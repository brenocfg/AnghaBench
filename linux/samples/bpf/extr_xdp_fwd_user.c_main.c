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
struct bpf_program {int dummy; } ;
struct bpf_prog_load_attr {char* file; int /*<<< orphan*/  prog_type; } ;
struct bpf_object {int dummy; } ;
typedef  int /*<<< orphan*/  filename ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_PROG_TYPE_XDP ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PATH_MAX ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  basename (char*) ; 
 int bpf_map__fd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_object__find_map_by_name (struct bpf_object*,char*) ; 
 struct bpf_program* bpf_object__find_program_by_title (struct bpf_object*,char const*) ; 
 int bpf_prog_load_xattr (struct bpf_prog_load_attr*,struct bpf_object**,int*) ; 
 int bpf_program__fd (struct bpf_program*) ; 
 int do_attach (int,int,int,char*) ; 
 int do_detach (int,char*) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int getopt (int,char**,char*) ; 
 int if_nametoindex (char*) ; 
 int optind ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 int strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

int main(int argc, char **argv)
{
	struct bpf_prog_load_attr prog_load_attr = {
		.prog_type	= BPF_PROG_TYPE_XDP,
	};
	const char *prog_name = "xdp_fwd";
	struct bpf_program *prog;
	int prog_fd, map_fd = -1;
	char filename[PATH_MAX];
	struct bpf_object *obj;
	int opt, i, idx, err;
	int attach = 1;
	int ret = 0;

	while ((opt = getopt(argc, argv, ":dD")) != -1) {
		switch (opt) {
		case 'd':
			attach = 0;
			break;
		case 'D':
			prog_name = "xdp_fwd_direct";
			break;
		default:
			usage(basename(argv[0]));
			return 1;
		}
	}

	if (optind == argc) {
		usage(basename(argv[0]));
		return 1;
	}

	if (attach) {
		snprintf(filename, sizeof(filename), "%s_kern.o", argv[0]);
		prog_load_attr.file = filename;

		if (access(filename, O_RDONLY) < 0) {
			printf("error accessing file %s: %s\n",
				filename, strerror(errno));
			return 1;
		}

		err = bpf_prog_load_xattr(&prog_load_attr, &obj, &prog_fd);
		if (err) {
			printf("Does kernel support devmap lookup?\n");
			/* If not, the error message will be:
			 *  "cannot pass map_type 14 into func bpf_map_lookup_elem#1"
			 */
			return 1;
		}

		prog = bpf_object__find_program_by_title(obj, prog_name);
		prog_fd = bpf_program__fd(prog);
		if (prog_fd < 0) {
			printf("program not found: %s\n", strerror(prog_fd));
			return 1;
		}
		map_fd = bpf_map__fd(bpf_object__find_map_by_name(obj,
							"xdp_tx_ports"));
		if (map_fd < 0) {
			printf("map not found: %s\n", strerror(map_fd));
			return 1;
		}
	}

	for (i = optind; i < argc; ++i) {
		idx = if_nametoindex(argv[i]);
		if (!idx)
			idx = strtoul(argv[i], NULL, 0);

		if (!idx) {
			fprintf(stderr, "Invalid arg\n");
			return 1;
		}
		if (!attach) {
			err = do_detach(idx, argv[i]);
			if (err)
				ret = err;
		} else {
			err = do_attach(idx, prog_fd, map_fd, argv[i]);
			if (err)
				ret = err;
		}
	}

	return ret;
}