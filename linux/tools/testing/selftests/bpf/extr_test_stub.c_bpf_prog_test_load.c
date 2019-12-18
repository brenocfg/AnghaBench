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
struct bpf_prog_load_attr {char const* file; int prog_type; int /*<<< orphan*/  prog_flags; scalar_t__ expected_attach_type; } ;
struct bpf_object {int dummy; } ;
typedef  enum bpf_prog_type { ____Placeholder_bpf_prog_type } bpf_prog_type ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_F_TEST_RND_HI32 ; 
 int bpf_prog_load_xattr (struct bpf_prog_load_attr*,struct bpf_object**,int*) ; 
 int /*<<< orphan*/  memset (struct bpf_prog_load_attr*,int /*<<< orphan*/ ,int) ; 

int bpf_prog_test_load(const char *file, enum bpf_prog_type type,
		       struct bpf_object **pobj, int *prog_fd)
{
	struct bpf_prog_load_attr attr;

	memset(&attr, 0, sizeof(struct bpf_prog_load_attr));
	attr.file = file;
	attr.prog_type = type;
	attr.expected_attach_type = 0;
	attr.prog_flags = BPF_F_TEST_RND_HI32;

	return bpf_prog_load_xattr(&attr, pobj, prog_fd);
}