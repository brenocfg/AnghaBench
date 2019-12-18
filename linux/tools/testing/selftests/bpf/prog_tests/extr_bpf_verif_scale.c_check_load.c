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
struct bpf_prog_load_attr {char const* file; int prog_type; int log_level; int /*<<< orphan*/  prog_flags; } ;
struct bpf_object {int dummy; } ;
typedef  enum bpf_prog_type { ____Placeholder_bpf_prog_type } bpf_prog_type ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_F_TEST_RND_HI32 ; 
 int /*<<< orphan*/  bpf_object__close (struct bpf_object*) ; 
 int bpf_prog_load_xattr (struct bpf_prog_load_attr*,struct bpf_object**,int*) ; 
 int /*<<< orphan*/  memset (struct bpf_prog_load_attr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int check_load(const char *file, enum bpf_prog_type type)
{
	struct bpf_prog_load_attr attr;
	struct bpf_object *obj = NULL;
	int err, prog_fd;

	memset(&attr, 0, sizeof(struct bpf_prog_load_attr));
	attr.file = file;
	attr.prog_type = type;
	attr.log_level = 4;
	attr.prog_flags = BPF_F_TEST_RND_HI32;
	err = bpf_prog_load_xattr(&attr, &obj, &prog_fd);
	bpf_object__close(obj);
	return err;
}