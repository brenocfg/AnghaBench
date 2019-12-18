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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MAP_TYPE_CGROUP_ARRAY ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int bpf_create_map (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int bpf_map_update_elem (int,int*,int*,int /*<<< orphan*/ ) ; 
 int bpf_obj_get (char const*) ; 
 int bpf_obj_pin (int,char const*) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int getopt (int,char**,char*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char **argv)
{
	const char *pinned_file = NULL, *cg2 = NULL;
	int create_array = 1;
	int array_key = 0;
	int array_fd = -1;
	int cg2_fd = -1;
	int ret = -1;
	int opt;

	while ((opt = getopt(argc, argv, "F:U:v:")) != -1) {
		switch (opt) {
		/* General args */
		case 'F':
			pinned_file = optarg;
			break;
		case 'U':
			pinned_file = optarg;
			create_array = 0;
			break;
		case 'v':
			cg2 = optarg;
			break;
		default:
			usage();
			goto out;
		}
	}

	if (!cg2 || !pinned_file) {
		usage();
		goto out;
	}

	cg2_fd = open(cg2, O_RDONLY);
	if (cg2_fd < 0) {
		fprintf(stderr, "open(%s,...): %s(%d)\n",
			cg2, strerror(errno), errno);
		goto out;
	}

	if (create_array) {
		array_fd = bpf_create_map(BPF_MAP_TYPE_CGROUP_ARRAY,
					  sizeof(uint32_t), sizeof(uint32_t),
					  1, 0);
		if (array_fd < 0) {
			fprintf(stderr,
				"bpf_create_map(BPF_MAP_TYPE_CGROUP_ARRAY,...): %s(%d)\n",
				strerror(errno), errno);
			goto out;
		}
	} else {
		array_fd = bpf_obj_get(pinned_file);
		if (array_fd < 0) {
			fprintf(stderr, "bpf_obj_get(%s): %s(%d)\n",
				pinned_file, strerror(errno), errno);
			goto out;
		}
	}

	ret = bpf_map_update_elem(array_fd, &array_key, &cg2_fd, 0);
	if (ret) {
		perror("bpf_map_update_elem");
		goto out;
	}

	if (create_array) {
		ret = bpf_obj_pin(array_fd, pinned_file);
		if (ret) {
			fprintf(stderr, "bpf_obj_pin(..., %s): %s(%d)\n",
				pinned_file, strerror(errno), errno);
			goto out;
		}
	}

out:
	if (array_fd != -1)
		close(array_fd);
	if (cg2_fd != -1)
		close(cg2_fd);
	return ret;
}