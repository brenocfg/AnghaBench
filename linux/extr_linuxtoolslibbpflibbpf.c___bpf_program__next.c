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
struct bpf_program {struct bpf_object* obj; } ;
struct bpf_object {size_t nr_programs; struct bpf_program* programs; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_warning (char*) ; 

__attribute__((used)) static struct bpf_program *
__bpf_program__next(struct bpf_program *prev, struct bpf_object *obj)
{
	size_t idx;

	if (!obj->programs)
		return NULL;
	/* First handler */
	if (prev == NULL)
		return &obj->programs[0];

	if (prev->obj != obj) {
		pr_warning("error: program handler doesn't match object\n");
		return NULL;
	}

	idx = (prev - obj->programs) + 1;
	if (idx >= obj->nr_programs)
		return NULL;
	return &obj->programs[idx];
}