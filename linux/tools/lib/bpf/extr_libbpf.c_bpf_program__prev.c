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

/* Variables and functions */
 struct bpf_program* __bpf_program__iter (struct bpf_program*,struct bpf_object const*,int) ; 
 scalar_t__ bpf_program__is_function_storage (struct bpf_program*,struct bpf_object const*) ; 

struct bpf_program *
bpf_program__prev(struct bpf_program *next, const struct bpf_object *obj)
{
	struct bpf_program *prog = next;

	do {
		prog = __bpf_program__iter(prog, obj, false);
	} while (prog && bpf_program__is_function_storage(prog, obj));

	return prog;
}