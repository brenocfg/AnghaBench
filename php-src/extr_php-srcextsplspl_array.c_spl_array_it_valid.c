#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ zend_object_iterator ;
struct TYPE_9__ {int ar_flags; } ;
typedef  TYPE_2__ spl_array_object ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int SPL_ARRAY_OVERLOADED_VALID ; 
 TYPE_2__* Z_SPLARRAY_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * spl_array_get_hash_table (TYPE_2__*) ; 
 int /*<<< orphan*/  spl_array_get_pos_ptr (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int zend_hash_has_more_elements_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zend_user_it_valid (TYPE_1__*) ; 

__attribute__((used)) static int spl_array_it_valid(zend_object_iterator *iter) /* {{{ */
{
	spl_array_object *object = Z_SPLARRAY_P(&iter->data);
	HashTable *aht = spl_array_get_hash_table(object);

	if (object->ar_flags & SPL_ARRAY_OVERLOADED_VALID) {
		return zend_user_it_valid(iter);
	} else {
		return zend_hash_has_more_elements_ex(aht, spl_array_get_pos_ptr(aht, object));
	}
}