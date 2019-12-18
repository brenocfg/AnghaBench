#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* data; TYPE_2__* rodata; } ;
struct bpf_object {size_t nr_maps; size_t nr_programs; int /*<<< orphan*/  list; TYPE_2__* programs; TYPE_2__* maps; TYPE_1__ sections; int /*<<< orphan*/  btf_ext; int /*<<< orphan*/  btf; int /*<<< orphan*/  priv; int /*<<< orphan*/  (* clear_priv ) (struct bpf_object*,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  (* clear_priv ) (TYPE_2__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * priv; struct TYPE_6__* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_object__elf_finish (struct bpf_object*) ; 
 int /*<<< orphan*/  bpf_object__unload (struct bpf_object*) ; 
 int /*<<< orphan*/  bpf_program__exit (TYPE_2__*) ; 
 int /*<<< orphan*/  btf__free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btf_ext__free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct bpf_object*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct bpf_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfree (TYPE_2__**) ; 

void bpf_object__close(struct bpf_object *obj)
{
	size_t i;

	if (!obj)
		return;

	if (obj->clear_priv)
		obj->clear_priv(obj, obj->priv);

	bpf_object__elf_finish(obj);
	bpf_object__unload(obj);
	btf__free(obj->btf);
	btf_ext__free(obj->btf_ext);

	for (i = 0; i < obj->nr_maps; i++) {
		zfree(&obj->maps[i].name);
		if (obj->maps[i].clear_priv)
			obj->maps[i].clear_priv(&obj->maps[i],
						obj->maps[i].priv);
		obj->maps[i].priv = NULL;
		obj->maps[i].clear_priv = NULL;
	}

	zfree(&obj->sections.rodata);
	zfree(&obj->sections.data);
	zfree(&obj->maps);
	obj->nr_maps = 0;

	if (obj->programs && obj->nr_programs) {
		for (i = 0; i < obj->nr_programs; i++)
			bpf_program__exit(&obj->programs[i]);
	}
	zfree(&obj->programs);

	list_del(&obj->list);
	free(obj);
}