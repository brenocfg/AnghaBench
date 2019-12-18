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
typedef  int /*<<< orphan*/  zval ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ zend_object_iterator ;
struct TYPE_9__ {int ar_flags; } ;
typedef  TYPE_2__ spl_array_object ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 scalar_t__ IS_INDIRECT ; 
 int SPL_ARRAY_OVERLOADED_CURRENT ; 
 int /*<<< orphan*/ * Z_INDIRECT_P (int /*<<< orphan*/ *) ; 
 TYPE_2__* Z_SPLARRAY_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * spl_array_get_hash_table (TYPE_2__*) ; 
 int /*<<< orphan*/  spl_array_get_pos_ptr (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * zend_hash_get_current_data_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_user_it_get_current_data (TYPE_1__*) ; 

__attribute__((used)) static zval *spl_array_it_get_current_data(zend_object_iterator *iter) /* {{{ */
{
	spl_array_object *object = Z_SPLARRAY_P(&iter->data);
	HashTable *aht = spl_array_get_hash_table(object);

	if (object->ar_flags & SPL_ARRAY_OVERLOADED_CURRENT) {
		return zend_user_it_get_current_data(iter);
	} else {
		zval *data = zend_hash_get_current_data_ex(aht, spl_array_get_pos_ptr(aht, object));
		if (data && Z_TYPE_P(data) == IS_INDIRECT) {
			data = Z_INDIRECT_P(data);
		}
		return data;
	}
}