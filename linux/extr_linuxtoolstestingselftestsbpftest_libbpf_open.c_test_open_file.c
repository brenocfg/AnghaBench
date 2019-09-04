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
struct bpf_object {int dummy; } ;
typedef  int /*<<< orphan*/  err_buf ;

/* Variables and functions */
 int EXIT_FAIL_LIBBPF ; 
 int /*<<< orphan*/  bpf_object__close (struct bpf_object*) ; 
 char* bpf_object__name (struct bpf_object*) ; 
 struct bpf_object* bpf_object__open (char*) ; 
 long libbpf_get_error (struct bpf_object*) ; 
 int /*<<< orphan*/  libbpf_strerror (long,char*,int) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  test_walk_maps (struct bpf_object*,int) ; 
 int /*<<< orphan*/  test_walk_progs (struct bpf_object*,int) ; 

int test_open_file(char *filename, bool verbose)
{
	struct bpf_object *bpfobj = NULL;
	long err;

	if (verbose)
		printf("Open BPF ELF-file with libbpf: %s\n", filename);

	/* Load BPF ELF object file and check for errors */
	bpfobj = bpf_object__open(filename);
	err = libbpf_get_error(bpfobj);
	if (err) {
		char err_buf[128];
		libbpf_strerror(err, err_buf, sizeof(err_buf));
		if (verbose)
			printf("Unable to load eBPF objects in file '%s': %s\n",
			       filename, err_buf);
		return EXIT_FAIL_LIBBPF;
	}
	test_walk_progs(bpfobj, verbose);
	test_walk_maps(bpfobj, verbose);

	if (verbose)
		printf("Close BPF ELF-file with libbpf: %s\n",
		       bpf_object__name(bpfobj));
	bpf_object__close(bpfobj);

	return 0;
}