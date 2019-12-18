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
struct bpf_map_info {int dummy; } ;
typedef  int /*<<< orphan*/  info ;
typedef  int __u32 ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int alloc_key_value (struct bpf_map_info*,void**,void**) ; 
 int bpf_map_lookup_and_delete_elem (int,void*,void*) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ json_output ; 
 int /*<<< orphan*/  json_wtr ; 
 int /*<<< orphan*/  jsonw_null (int /*<<< orphan*/ ) ; 
 int map_parse_fd_and_info (int*,char***,struct bpf_map_info*,int*) ; 
 int /*<<< orphan*/  p_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_key_value (struct bpf_map_info*,void*,void*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  usage () ; 

__attribute__((used)) static int do_pop_dequeue(int argc, char **argv)
{
	struct bpf_map_info info = {};
	__u32 len = sizeof(info);
	void *key, *value;
	int err;
	int fd;

	if (argc < 2)
		usage();

	fd = map_parse_fd_and_info(&argc, &argv, &info, &len);
	if (fd < 0)
		return -1;

	err = alloc_key_value(&info, &key, &value);
	if (err)
		goto exit_free;

	err = bpf_map_lookup_and_delete_elem(fd, key, value);
	if (err) {
		if (errno == ENOENT) {
			if (json_output)
				jsonw_null(json_wtr);
			else
				printf("Error: empty map\n");
		} else {
			p_err("pop failed: %s", strerror(errno));
		}

		goto exit_free;
	}

	print_key_value(&info, key, value);

exit_free:
	free(key);
	free(value);
	close(fd);

	return err;
}