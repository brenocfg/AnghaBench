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
struct sock_addr_test {scalar_t__ expected_result; int /*<<< orphan*/  expected_attach_type; } ;
struct bpf_prog_load_attr {char const* file; int /*<<< orphan*/  prog_flags; int /*<<< orphan*/  expected_attach_type; int /*<<< orphan*/  prog_type; } ;
struct bpf_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_F_TEST_RND_HI32 ; 
 int /*<<< orphan*/  BPF_PROG_TYPE_CGROUP_SOCK_ADDR ; 
 scalar_t__ LOAD_REJECT ; 
 scalar_t__ bpf_prog_load_xattr (struct bpf_prog_load_attr*,struct bpf_object**,int*) ; 
 int /*<<< orphan*/  log_err (char*,char const*) ; 
 int /*<<< orphan*/  memset (struct bpf_prog_load_attr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int load_path(const struct sock_addr_test *test, const char *path)
{
	struct bpf_prog_load_attr attr;
	struct bpf_object *obj;
	int prog_fd;

	memset(&attr, 0, sizeof(struct bpf_prog_load_attr));
	attr.file = path;
	attr.prog_type = BPF_PROG_TYPE_CGROUP_SOCK_ADDR;
	attr.expected_attach_type = test->expected_attach_type;
	attr.prog_flags = BPF_F_TEST_RND_HI32;

	if (bpf_prog_load_xattr(&attr, &obj, &prog_fd)) {
		if (test->expected_result != LOAD_REJECT)
			log_err(">>> Loading program (%s) error.\n", path);
		return -1;
	}

	return prog_fd;
}