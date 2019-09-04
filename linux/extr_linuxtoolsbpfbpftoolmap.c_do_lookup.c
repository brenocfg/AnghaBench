#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct btf_dumper {int is_plain_text; int /*<<< orphan*/ * jw; struct btf* btf; } ;
struct btf {int dummy; } ;
struct bpf_map_info {int /*<<< orphan*/  key_size; } ;
typedef  int /*<<< orphan*/  json_writer_t ;
typedef  int /*<<< orphan*/  info ;
typedef  int __u32 ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 void* alloc_value (struct bpf_map_info*) ; 
 int bpf_map_lookup_elem (int,void*,void*) ; 
 int /*<<< orphan*/  btf__free (struct btf*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  do_dump_btf (struct btf_dumper*,struct bpf_map_info*,void*,void*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprint_hex (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int get_btf (struct bpf_map_info*,struct btf**) ; 
 int /*<<< orphan*/ * get_btf_writer () ; 
 scalar_t__ json_output ; 
 int /*<<< orphan*/  json_wtr ; 
 int /*<<< orphan*/  jsonw_destroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  jsonw_null (int /*<<< orphan*/ ) ; 
 void* malloc (int /*<<< orphan*/ ) ; 
 int map_parse_fd_and_info (int*,char***,struct bpf_map_info*,int*) ; 
 int /*<<< orphan*/  p_err (char*,...) ; 
 int /*<<< orphan*/  p_info (char*) ; 
 int parse_elem (char**,struct bpf_map_info*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_entry_json (struct bpf_map_info*,void*,void*,struct btf*) ; 
 int /*<<< orphan*/  print_entry_plain (struct bpf_map_info*,void*,void*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  usage () ; 

__attribute__((used)) static int do_lookup(int argc, char **argv)
{
	struct bpf_map_info info = {};
	__u32 len = sizeof(info);
	json_writer_t *btf_wtr;
	struct btf *btf = NULL;
	void *key, *value;
	int err;
	int fd;

	if (argc < 2)
		usage();

	fd = map_parse_fd_and_info(&argc, &argv, &info, &len);
	if (fd < 0)
		return -1;

	key = malloc(info.key_size);
	value = alloc_value(&info);
	if (!key || !value) {
		p_err("mem alloc failed");
		err = -1;
		goto exit_free;
	}

	err = parse_elem(argv, &info, key, NULL, info.key_size, 0, NULL, NULL);
	if (err)
		goto exit_free;

	err = bpf_map_lookup_elem(fd, key, value);
	if (err) {
		if (errno == ENOENT) {
			if (json_output) {
				jsonw_null(json_wtr);
			} else {
				printf("key:\n");
				fprint_hex(stdout, key, info.key_size, " ");
				printf("\n\nNot found\n");
			}
		} else {
			p_err("lookup failed: %s", strerror(errno));
		}

		goto exit_free;
	}

	/* here means bpf_map_lookup_elem() succeeded */
	err = get_btf(&info, &btf);
	if (err) {
		p_err("failed to get btf");
		goto exit_free;
	}

	if (json_output) {
		print_entry_json(&info, key, value, btf);
	} else if (btf) {
		/* if here json_wtr wouldn't have been initialised,
		 * so let's create separate writer for btf
		 */
		btf_wtr = get_btf_writer();
		if (!btf_wtr) {
			p_info("failed to create json writer for btf. falling back to plain output");
			btf__free(btf);
			btf = NULL;
			print_entry_plain(&info, key, value);
		} else {
			struct btf_dumper d = {
				.btf = btf,
				.jw = btf_wtr,
				.is_plain_text = true,
			};

			do_dump_btf(&d, &info, key, value);
			jsonw_destroy(&btf_wtr);
		}
	} else {
		print_entry_plain(&info, key, value);
	}

exit_free:
	free(key);
	free(value);
	close(fd);
	btf__free(btf);

	return err;
}