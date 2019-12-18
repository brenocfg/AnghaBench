#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ zend_object_iterator ;
struct TYPE_10__ {int ar_flags; } ;
typedef  TYPE_2__ spl_array_object ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int SPL_ARRAY_OVERLOADED_NEXT ; 
 TYPE_2__* Z_SPLARRAY_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * spl_array_get_hash_table (TYPE_2__*) ; 
 int /*<<< orphan*/  spl_array_next_ex (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_user_it_invalidate_current (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_user_it_move_forward (TYPE_1__*) ; 

__attribute__((used)) static void spl_array_it_move_forward(zend_object_iterator *iter) /* {{{ */
{
	spl_array_object *object = Z_SPLARRAY_P(&iter->data);
	HashTable *aht = spl_array_get_hash_table(object);

	if (object->ar_flags & SPL_ARRAY_OVERLOADED_NEXT) {
		zend_user_it_move_forward(iter);
	} else {
		zend_user_it_invalidate_current(iter);
		spl_array_next_ex(object, aht);
	}
}