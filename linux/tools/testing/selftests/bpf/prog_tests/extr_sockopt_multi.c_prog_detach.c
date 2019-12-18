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
struct bpf_object {int dummy; } ;
typedef  enum bpf_prog_type { ____Placeholder_bpf_prog_type } bpf_prog_type ;
typedef  enum bpf_attach_type { ____Placeholder_bpf_attach_type } bpf_attach_type ;

/* Variables and functions */
 struct bpf_program* bpf_object__find_program_by_title (struct bpf_object*,char const*) ; 
 int bpf_prog_detach2 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bpf_program__fd (struct bpf_program*) ; 
 int libbpf_prog_type_by_name (char const*,int*,int*) ; 

__attribute__((used)) static int prog_detach(struct bpf_object *obj, int cgroup_fd, const char *title)
{
	enum bpf_attach_type attach_type;
	enum bpf_prog_type prog_type;
	struct bpf_program *prog;
	int err;

	err = libbpf_prog_type_by_name(title, &prog_type, &attach_type);
	if (err)
		return -1;

	prog = bpf_object__find_program_by_title(obj, title);
	if (!prog)
		return -1;

	err = bpf_prog_detach2(bpf_program__fd(prog), cgroup_fd,
			       attach_type);
	if (err)
		return -1;

	return 0;
}