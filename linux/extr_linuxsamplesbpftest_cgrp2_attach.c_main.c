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
typedef  enum bpf_attach_type { ____Placeholder_bpf_attach_type } bpf_attach_type ;

/* Variables and functions */
 int BPF_CGROUP_INET_EGRESS ; 
 int BPF_CGROUP_INET_INGRESS ; 
 int EXIT_FAILURE ; 
 int O_DIRECTORY ; 
 int O_RDONLY ; 
 int attach_filter (int,int,int) ; 
 int bpf_prog_detach (int,int) ; 
 int errno ; 
 int getopt (int,char**,char*) ; 
 int open (char*,int) ; 
 int optind ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strerror (int) ; 
 int usage (char*) ; 

int main(int argc, char **argv)
{
	int detach_only = 0, verdict = 1;
	enum bpf_attach_type type;
	int opt, cg_fd, ret;

	while ((opt = getopt(argc, argv, "Dd")) != -1) {
		switch (opt) {
		case 'd':
			verdict = 0;
			break;
		case 'D':
			detach_only = 1;
			break;
		default:
			return usage(argv[0]);
		}
	}

	if (argc - optind < 2)
		return usage(argv[0]);

	if (strcmp(argv[optind + 1], "ingress") == 0)
		type = BPF_CGROUP_INET_INGRESS;
	else if (strcmp(argv[optind + 1], "egress") == 0)
		type = BPF_CGROUP_INET_EGRESS;
	else
		return usage(argv[0]);

	cg_fd = open(argv[optind], O_DIRECTORY | O_RDONLY);
	if (cg_fd < 0) {
		printf("Failed to open cgroup path: '%s'\n", strerror(errno));
		return EXIT_FAILURE;
	}

	if (detach_only) {
		ret = bpf_prog_detach(cg_fd, type);
		printf("bpf_prog_detach() returned '%s' (%d)\n",
		       strerror(errno), errno);
	} else
		ret = attach_filter(cg_fd, type, verdict);

	return ret;
}