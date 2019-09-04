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

/* Variables and functions */
 int atoi (char*) ; 
 int bpf_map_update_elem (int,int*,int*,int /*<<< orphan*/ ) ; 
 int bpf_obj_get (char const*) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*,int) ; 
 int getopt (int,char**,char*) ; 
 char* optarg ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char **argv)
{
	const char *pinned_file = NULL;
	int ifindex = -1;
	int array_key = 0;
	int array_fd = -1;
	int ret = -1;
	int opt;

	while ((opt = getopt(argc, argv, "F:U:i:")) != -1) {
		switch (opt) {
		/* General args */
		case 'U':
			pinned_file = optarg;
			break;
		case 'i':
			ifindex = atoi(optarg);
			break;
		default:
			usage();
			goto out;
		}
	}

	if (ifindex < 0 || !pinned_file) {
		usage();
		goto out;
	}

	array_fd = bpf_obj_get(pinned_file);
	if (array_fd < 0) {
		fprintf(stderr, "bpf_obj_get(%s): %s(%d)\n",
			pinned_file, strerror(errno), errno);
		goto out;
	}

	/* bpf_tunnel_key.remote_ipv4 expects host byte orders */
	ret = bpf_map_update_elem(array_fd, &array_key, &ifindex, 0);
	if (ret) {
		perror("bpf_map_update_elem");
		goto out;
	}

out:
	if (array_fd != -1)
		close(array_fd);
	return ret;
}