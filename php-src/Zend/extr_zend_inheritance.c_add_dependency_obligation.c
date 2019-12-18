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
typedef  int /*<<< orphan*/  zend_class_entry ;
struct TYPE_4__ {int /*<<< orphan*/ * dependency_ce; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ variance_obligation ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  OBLIGATION_DEPENDENCY ; 
 TYPE_1__* emalloc (int) ; 
 int /*<<< orphan*/ * get_or_init_obligations_for_class (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_next_index_insert_ptr (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void add_dependency_obligation(zend_class_entry *ce, zend_class_entry *dependency_ce) {
	HashTable *obligations = get_or_init_obligations_for_class(ce);
	variance_obligation *obligation = emalloc(sizeof(variance_obligation));
	obligation->type = OBLIGATION_DEPENDENCY;
	obligation->dependency_ce = dependency_ce;
	zend_hash_next_index_insert_ptr(obligations, obligation);
}