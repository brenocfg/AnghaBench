#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ut32 ;
struct TYPE_6__ {int /*<<< orphan*/  free; } ;
struct TYPE_5__ {int /*<<< orphan*/ * binsym; TYPE_3__* mem; int /*<<< orphan*/  kv; TYPE_3__* lines; TYPE_3__* classes; TYPE_3__* symbols; int /*<<< orphan*/  strings_db; TYPE_3__* strings; TYPE_3__* sections; int /*<<< orphan*/  relocs; TYPE_3__* libs; TYPE_3__* imports; TYPE_3__* fields; TYPE_3__* entries; int /*<<< orphan*/  addr2klassmethod; } ;
typedef  TYPE_1__ RBinObject ;

/* Variables and functions */
 size_t R_BIN_SYM_LAST ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ht_up_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_free ; 
 int /*<<< orphan*/  r_list_free (TYPE_3__*) ; 
 int /*<<< orphan*/  r_rbtree_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_return_if_fail (TYPE_1__*) ; 
 int /*<<< orphan*/  reloc_free ; 
 int /*<<< orphan*/  sdb_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void object_delete_items(RBinObject *o) {
	ut32 i = 0;
	r_return_if_fail (o);
	sdb_free (o->addr2klassmethod);
	r_list_free (o->entries);
	r_list_free (o->fields);
	r_list_free (o->imports);
	r_list_free (o->libs);
	r_rbtree_free (o->relocs, reloc_free);
	r_list_free (o->sections);
	r_list_free (o->strings);
	ht_up_free (o->strings_db);
	r_list_free (o->symbols);
	r_list_free (o->classes);
	r_list_free (o->lines);
	sdb_free (o->kv);
	if (o->mem) {
		o->mem->free = mem_free;
	}
	r_list_free (o->mem);
	for (i = 0; i < R_BIN_SYM_LAST; i++) {
		free (o->binsym[i]);
	}
}