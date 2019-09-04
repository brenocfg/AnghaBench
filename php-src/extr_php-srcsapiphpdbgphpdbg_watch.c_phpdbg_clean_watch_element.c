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
struct TYPE_5__ {TYPE_3__* watch; int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ phpdbg_watch_element ;
struct TYPE_6__ {int /*<<< orphan*/  elements; } ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  phpdbg_remove_watchpoint (TYPE_3__*) ; 
 int /*<<< orphan*/  phpdbg_unwatch_parent_ht (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_hash_del (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zend_hash_num_elements (int /*<<< orphan*/ *) ; 

void phpdbg_clean_watch_element(phpdbg_watch_element *element) {
	HashTable *elements = &element->watch->elements;
	phpdbg_unwatch_parent_ht(element);
	zend_hash_del(elements, element->str);
	if (zend_hash_num_elements(elements) == 0) {
		phpdbg_remove_watchpoint(element->watch);
	}
}