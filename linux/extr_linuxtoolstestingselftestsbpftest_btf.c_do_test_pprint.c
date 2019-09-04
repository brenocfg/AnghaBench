#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
struct pprint_mapv {int ui32; int si32; int unused_bits2a; int bits28; int unused_bits2b; size_t aenum; int /*<<< orphan*/ * ui8a; int /*<<< orphan*/  ui64; } ;
struct btf_raw_test {char* descr; char* map_name; unsigned int max_entries; int ordered_map; int lossless_map; int /*<<< orphan*/  value_type_id; int /*<<< orphan*/  key_type_id; int /*<<< orphan*/  value_size; int /*<<< orphan*/  key_size; int /*<<< orphan*/  map_type; int /*<<< orphan*/  str_sec_size; int /*<<< orphan*/  str_sec; int /*<<< orphan*/  raw_types; } ;
struct bpf_create_map_attr {char* name; unsigned int max_entries; int btf_fd; int /*<<< orphan*/  btf_value_type_id; int /*<<< orphan*/  btf_key_type_id; int /*<<< orphan*/  value_size; int /*<<< orphan*/  key_size; int /*<<< orphan*/  map_type; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  pin_path ;
typedef  int /*<<< orphan*/  expected_line ;
struct TYPE_2__ {scalar_t__ always_log; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BTF_LOG_BUF_SIZE ; 
 scalar_t__ CHECK (int,char*,...) ; 
 TYPE_1__ args ; 
 unsigned int atoi (char*) ; 
 int bpf_create_map_xattr (struct bpf_create_map_attr*) ; 
 int bpf_load_btf (char*,unsigned int,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bpf_map_update_elem (int,unsigned int*,struct pprint_mapv*,int /*<<< orphan*/ ) ; 
 int bpf_obj_pin (int,char*) ; 
 char* btf_log_buf ; 
 char* btf_raw_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  close (int) ; 
 char* errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdr_tmpl ; 
 int /*<<< orphan*/ * pprint_enum_str ; 
 struct btf_raw_test pprint_test_template ; 
 int /*<<< orphan*/  set_pprint_mapv (struct pprint_mapv*,unsigned int) ; 
 void* snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static int do_test_pprint(void)
{
	const struct btf_raw_test *test = &pprint_test_template;
	struct bpf_create_map_attr create_attr = {};
	unsigned int key, nr_read_elems;
	bool ordered_map, lossless_map;
	int map_fd = -1, btf_fd = -1;
	struct pprint_mapv mapv = {};
	unsigned int raw_btf_size;
	char expected_line[255];
	FILE *pin_file = NULL;
	char pin_path[255];
	size_t line_len = 0;
	char *line = NULL;
	uint8_t *raw_btf;
	ssize_t nread;
	int err, ret;

	fprintf(stderr, "%s......", test->descr);
	raw_btf = btf_raw_create(&hdr_tmpl, test->raw_types,
				 test->str_sec, test->str_sec_size,
				 &raw_btf_size);

	if (!raw_btf)
		return -1;

	*btf_log_buf = '\0';
	btf_fd = bpf_load_btf(raw_btf, raw_btf_size,
			      btf_log_buf, BTF_LOG_BUF_SIZE,
			      args.always_log);
	free(raw_btf);

	if (CHECK(btf_fd == -1, "errno:%d", errno)) {
		err = -1;
		goto done;
	}

	create_attr.name = test->map_name;
	create_attr.map_type = test->map_type;
	create_attr.key_size = test->key_size;
	create_attr.value_size = test->value_size;
	create_attr.max_entries = test->max_entries;
	create_attr.btf_fd = btf_fd;
	create_attr.btf_key_type_id = test->key_type_id;
	create_attr.btf_value_type_id = test->value_type_id;

	map_fd = bpf_create_map_xattr(&create_attr);
	if (CHECK(map_fd == -1, "errno:%d", errno)) {
		err = -1;
		goto done;
	}

	ret = snprintf(pin_path, sizeof(pin_path), "%s/%s",
		       "/sys/fs/bpf", test->map_name);

	if (CHECK(ret == sizeof(pin_path), "pin_path %s/%s is too long",
		  "/sys/fs/bpf", test->map_name)) {
		err = -1;
		goto done;
	}

	err = bpf_obj_pin(map_fd, pin_path);
	if (CHECK(err, "bpf_obj_pin(%s): errno:%d.", pin_path, errno))
		goto done;

	for (key = 0; key < test->max_entries; key++) {
		set_pprint_mapv(&mapv, key);
		bpf_map_update_elem(map_fd, &key, &mapv, 0);
	}

	pin_file = fopen(pin_path, "r");
	if (CHECK(!pin_file, "fopen(%s): errno:%d", pin_path, errno)) {
		err = -1;
		goto done;
	}

	/* Skip lines start with '#' */
	while ((nread = getline(&line, &line_len, pin_file)) > 0 &&
	       *line == '#')
		;

	if (CHECK(nread <= 0, "Unexpected EOF")) {
		err = -1;
		goto done;
	}

	nr_read_elems = 0;
	ordered_map = test->ordered_map;
	lossless_map = test->lossless_map;
	do {
		ssize_t nexpected_line;
		unsigned int next_key;

		next_key = ordered_map ? nr_read_elems : atoi(line);
		set_pprint_mapv(&mapv, next_key);
		nexpected_line = snprintf(expected_line, sizeof(expected_line),
					  "%u: {%u,0,%d,0x%x,0x%x,0x%x,{%lu|[%u,%u,%u,%u,%u,%u,%u,%u]},%s}\n",
					  next_key,
					  mapv.ui32, mapv.si32,
					  mapv.unused_bits2a, mapv.bits28, mapv.unused_bits2b,
					  mapv.ui64,
					  mapv.ui8a[0], mapv.ui8a[1], mapv.ui8a[2], mapv.ui8a[3],
					  mapv.ui8a[4], mapv.ui8a[5], mapv.ui8a[6], mapv.ui8a[7],
					  pprint_enum_str[mapv.aenum]);

		if (CHECK(nexpected_line == sizeof(expected_line),
			  "expected_line is too long")) {
			err = -1;
			goto done;
		}

		if (strcmp(expected_line, line)) {
			err = -1;
			fprintf(stderr, "unexpected pprint output\n");
			fprintf(stderr, "expected: %s", expected_line);
			fprintf(stderr, "    read: %s", line);
			goto done;
		}

		nread = getline(&line, &line_len, pin_file);
	} while (++nr_read_elems < test->max_entries && nread > 0);

	if (lossless_map &&
	    CHECK(nr_read_elems < test->max_entries,
		  "Unexpected EOF. nr_read_elems:%u test->max_entries:%u",
		  nr_read_elems, test->max_entries)) {
		err = -1;
		goto done;
	}

	if (CHECK(nread > 0, "Unexpected extra pprint output: %s", line)) {
		err = -1;
		goto done;
	}

	err = 0;

done:
	if (!err)
		fprintf(stderr, "OK");
	if (*btf_log_buf && (err || args.always_log))
		fprintf(stderr, "\n%s", btf_log_buf);
	if (btf_fd != -1)
		close(btf_fd);
	if (map_fd != -1)
		close(map_fd);
	if (pin_file)
		fclose(pin_file);
	unlink(pin_path);
	free(line);

	return err;
}