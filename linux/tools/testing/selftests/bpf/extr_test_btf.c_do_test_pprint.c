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
struct btf_raw_test {int mapv_kind; char* descr; char* map_name; unsigned int max_entries; int percpu_map; int ordered_map; int lossless_map; int /*<<< orphan*/  value_type_id; int /*<<< orphan*/  key_type_id; int /*<<< orphan*/  value_size; int /*<<< orphan*/  key_size; int /*<<< orphan*/  map_type; int /*<<< orphan*/  str_sec_size; int /*<<< orphan*/  str_sec; int /*<<< orphan*/  raw_types; } ;
struct bpf_create_map_attr {char* name; unsigned int max_entries; int btf_fd; int /*<<< orphan*/  btf_value_type_id; int /*<<< orphan*/  btf_key_type_id; int /*<<< orphan*/  value_size; int /*<<< orphan*/  key_size; int /*<<< orphan*/  map_type; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  pin_path ;
typedef  int /*<<< orphan*/  expected_line ;
typedef  enum pprint_mapv_kind_t { ____Placeholder_pprint_mapv_kind_t } pprint_mapv_kind_t ;
struct TYPE_2__ {scalar_t__ always_log; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BTF_LOG_BUF_SIZE ; 
 scalar_t__ CHECK (int,char*,...) ; 
 TYPE_1__ args ; 
 unsigned int atoi (char*) ; 
 int bpf_create_map_xattr (struct bpf_create_map_attr*) ; 
 int bpf_load_btf (char*,unsigned int,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bpf_map_update_elem (int,unsigned int*,void*,int /*<<< orphan*/ ) ; 
 int bpf_num_possible_cpus () ; 
 int bpf_obj_pin (int,char*) ; 
 char* btf_log_buf ; 
 char* btf_raw_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ *) ; 
 void* calloc (int,int) ; 
 int check_line (char*,scalar_t__,int,char*) ; 
 int /*<<< orphan*/  close (int) ; 
 char* errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ get_pprint_expected_line (int,char*,int,int,unsigned int,int,void*) ; 
 int /*<<< orphan*/  get_pprint_mapv_size (int) ; 
 scalar_t__ getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdr_tmpl ; 
 struct btf_raw_test* pprint_test_template ; 
 int round_up (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_pprint_mapv (int,void*,unsigned int,int,int) ; 
 void* snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static int do_test_pprint(int test_num)
{
	const struct btf_raw_test *test = &pprint_test_template[test_num];
	enum pprint_mapv_kind_t mapv_kind = test->mapv_kind;
	struct bpf_create_map_attr create_attr = {};
	bool ordered_map, lossless_map, percpu_map;
	int err, ret, num_cpus, rounded_value_size;
	unsigned int key, nr_read_elems;
	int map_fd = -1, btf_fd = -1;
	unsigned int raw_btf_size;
	char expected_line[255];
	FILE *pin_file = NULL;
	char pin_path[255];
	size_t line_len = 0;
	char *line = NULL;
	void *mapv = NULL;
	uint8_t *raw_btf;
	ssize_t nread;

	fprintf(stderr, "%s(#%d)......", test->descr, test_num);
	raw_btf = btf_raw_create(&hdr_tmpl, test->raw_types,
				 test->str_sec, test->str_sec_size,
				 &raw_btf_size, NULL);

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

	percpu_map = test->percpu_map;
	num_cpus = percpu_map ? bpf_num_possible_cpus() : 1;
	rounded_value_size = round_up(get_pprint_mapv_size(mapv_kind), 8);
	mapv = calloc(num_cpus, rounded_value_size);
	if (CHECK(!mapv, "mapv allocation failure")) {
		err = -1;
		goto done;
	}

	for (key = 0; key < test->max_entries; key++) {
		set_pprint_mapv(mapv_kind, mapv, key, num_cpus, rounded_value_size);
		bpf_map_update_elem(map_fd, &key, mapv, 0);
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
		void *cmapv;
		int cpu;

		next_key = ordered_map ? nr_read_elems : atoi(line);
		set_pprint_mapv(mapv_kind, mapv, next_key, num_cpus, rounded_value_size);
		cmapv = mapv;

		for (cpu = 0; cpu < num_cpus; cpu++) {
			if (percpu_map) {
				/* for percpu map, the format looks like:
				 * <key>: {
				 *	cpu0: <value_on_cpu0>
				 *	cpu1: <value_on_cpu1>
				 *	...
				 *	cpun: <value_on_cpun>
				 * }
				 *
				 * let us verify the line containing the key here.
				 */
				if (cpu == 0) {
					nexpected_line = snprintf(expected_line,
								  sizeof(expected_line),
								  "%u: {\n",
								  next_key);

					err = check_line(expected_line, nexpected_line,
							 sizeof(expected_line), line);
					if (err == -1)
						goto done;
				}

				/* read value@cpu */
				nread = getline(&line, &line_len, pin_file);
				if (nread < 0)
					break;
			}

			nexpected_line = get_pprint_expected_line(mapv_kind, expected_line,
								  sizeof(expected_line),
								  percpu_map, next_key,
								  cpu, cmapv);
			err = check_line(expected_line, nexpected_line,
					 sizeof(expected_line), line);
			if (err == -1)
				goto done;

			cmapv = cmapv + rounded_value_size;
		}

		if (percpu_map) {
			/* skip the last bracket for the percpu map */
			nread = getline(&line, &line_len, pin_file);
			if (nread < 0)
				break;
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
	if (mapv)
		free(mapv);
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