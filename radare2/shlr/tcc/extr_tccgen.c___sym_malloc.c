#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* next; } ;
typedef  TYPE_1__ Sym ;

/* Variables and functions */
 int SYM_POOL_NB ; 
 int /*<<< orphan*/  dynarray_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nb_sym_pools ; 
 TYPE_1__* sym_free_first ; 
 int /*<<< orphan*/  sym_pools ; 

__attribute__((used)) static Sym *__sym_malloc(void) {
	Sym *sym_pool, *sym, *last_sym;
	int i;
	int sym_pool_size = SYM_POOL_NB * sizeof(Sym);
	sym_pool = malloc (sym_pool_size);
	memset (sym_pool, 0, sym_pool_size);
	dynarray_add (&sym_pools, &nb_sym_pools, sym_pool);

	last_sym = sym_free_first;
	sym = sym_pool;
	for (i = 0; i < SYM_POOL_NB; i++) {
		sym->next = last_sym;
		last_sym = sym;
		sym++;
	}
	sym_free_first = last_sym;
	return last_sym;
}