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
struct bpf_map_info {int /*<<< orphan*/  key_size; } ;
typedef  int /*<<< orphan*/  info ;
typedef  int __u32 ;

/* Variables and functions */
 int bpf_map_get_next_key (int,void*,void*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprint_hex (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ json_output ; 
 int /*<<< orphan*/  json_wtr ; 
 int /*<<< orphan*/  jsonw_end_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jsonw_null_field (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jsonw_start_object (int /*<<< orphan*/ ) ; 
 void* malloc (int /*<<< orphan*/ ) ; 
 int map_parse_fd_and_info (int*,char***,struct bpf_map_info*,int*) ; 
 int /*<<< orphan*/  p_err (char*,...) ; 
 int parse_elem (char**,struct bpf_map_info*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_hex_data_json (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

__attribute__((used)) static int do_getnext(int argc, char **argv)
{
	struct bpf_map_info info = {};
	__u32 len = sizeof(info);
	void *key, *nextkey;
	int err;
	int fd;

	if (argc < 2)
		usage();

	fd = map_parse_fd_and_info(&argc, &argv, &info, &len);
	if (fd < 0)
		return -1;

	key = malloc(info.key_size);
	nextkey = malloc(info.key_size);
	if (!key || !nextkey) {
		p_err("mem alloc failed");
		err = -1;
		goto exit_free;
	}

	if (argc) {
		err = parse_elem(argv, &info, key, NULL, info.key_size, 0,
				 NULL, NULL);
		if (err)
			goto exit_free;
	} else {
		free(key);
		key = NULL;
	}

	err = bpf_map_get_next_key(fd, key, nextkey);
	if (err) {
		p_err("can't get next key: %s", strerror(errno));
		goto exit_free;
	}

	if (json_output) {
		jsonw_start_object(json_wtr);
		if (key) {
			jsonw_name(json_wtr, "key");
			print_hex_data_json(key, info.key_size);
		} else {
			jsonw_null_field(json_wtr, "key");
		}
		jsonw_name(json_wtr, "next_key");
		print_hex_data_json(nextkey, info.key_size);
		jsonw_end_object(json_wtr);
	} else {
		if (key) {
			printf("key:\n");
			fprint_hex(stdout, key, info.key_size, " ");
			printf("\n");
		} else {
			printf("key: None\n");
		}
		printf("next key:\n");
		fprint_hex(stdout, nextkey, info.key_size, " ");
		printf("\n");
	}

exit_free:
	free(nextkey);
	free(key);
	close(fd);

	return err;
}