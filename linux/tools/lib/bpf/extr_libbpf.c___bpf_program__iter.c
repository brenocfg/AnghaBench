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
typedef  struct bpf_program {struct bpf_object const* obj; } const bpf_program ;
struct bpf_object {size_t nr_programs; struct bpf_program const* programs; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  pr_warning (char*) ; 

__attribute__((used)) static struct bpf_program *
__bpf_program__iter(const struct bpf_program *p, const struct bpf_object *obj,
		    bool forward)
{
	size_t nr_programs = obj->nr_programs;
	ssize_t idx;

	if (!nr_programs)
		return NULL;

	if (!p)
		/* Iter from the beginning */
		return forward ? &obj->programs[0] :
			&obj->programs[nr_programs - 1];

	if (p->obj != obj) {
		pr_warning("error: program handler doesn't match object\n");
		return NULL;
	}

	idx = (p - obj->programs) + (forward ? 1 : -1);
	if (idx >= obj->nr_programs || idx < 0)
		return NULL;
	return &obj->programs[idx];
}