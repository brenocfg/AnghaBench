#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bpf_object {size_t nr_maps; size_t nr_programs; int /*<<< orphan*/ * programs; TYPE_1__* maps; } ;
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  bpf_program__unload (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zclose (int /*<<< orphan*/ ) ; 

int bpf_object__unload(struct bpf_object *obj)
{
	size_t i;

	if (!obj)
		return -EINVAL;

	for (i = 0; i < obj->nr_maps; i++)
		zclose(obj->maps[i].fd);

	for (i = 0; i < obj->nr_programs; i++)
		bpf_program__unload(&obj->programs[i]);

	return 0;
}