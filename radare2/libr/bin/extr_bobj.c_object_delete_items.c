#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ut32 ;
struct TYPE_4__ {int /*<<< orphan*/ * binsym; int /*<<< orphan*/  mem; int /*<<< orphan*/  kv; int /*<<< orphan*/  lines; int /*<<< orphan*/  methods_ht; int /*<<< orphan*/  classes_ht; int /*<<< orphan*/  classes; int /*<<< orphan*/  symbols; int /*<<< orphan*/  strings_db; int /*<<< orphan*/  strings; int /*<<< orphan*/  sections; int /*<<< orphan*/  relocs; int /*<<< orphan*/  libs; int /*<<< orphan*/  imports; int /*<<< orphan*/  fields; int /*<<< orphan*/  entries; int /*<<< orphan*/  addr2klassmethod; } ;
typedef  TYPE_1__ RBinObject ;

/* Variables and functions */
 size_t R_BIN_SYM_LAST ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ht_pp_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ht_up_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ ) ; 
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
	ht_pp_free (o->classes_ht);
	ht_pp_free (o->methods_ht);
	r_list_free (o->lines);
	sdb_free (o->kv);
	r_list_free (o->mem);
	for (i = 0; i < R_BIN_SYM_LAST; i++) {
		free (o->binsym[i]);
	}
}