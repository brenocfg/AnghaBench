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
struct bpf_prog_load_attr {char* file; } ;
struct bpf_object {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHECK_FAIL (int) ; 
 int /*<<< orphan*/  bpf_object__close (struct bpf_object*) ; 
 int bpf_prog_load_xattr (struct bpf_prog_load_attr*,struct bpf_object**,int*) ; 
 int getsetsockopt () ; 
 int prog_attach (struct bpf_object*,int,char*) ; 

__attribute__((used)) static void run_test(int cgroup_fd)
{
	struct bpf_prog_load_attr attr = {
		.file = "./sockopt_sk.o",
	};
	struct bpf_object *obj;
	int ignored;
	int err;

	err = bpf_prog_load_xattr(&attr, &obj, &ignored);
	if (CHECK_FAIL(err))
		return;

	err = prog_attach(obj, cgroup_fd, "cgroup/getsockopt");
	if (CHECK_FAIL(err))
		goto close_bpf_object;

	err = prog_attach(obj, cgroup_fd, "cgroup/setsockopt");
	if (CHECK_FAIL(err))
		goto close_bpf_object;

	CHECK_FAIL(getsetsockopt());

close_bpf_object:
	bpf_object__close(obj);
}