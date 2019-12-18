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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ php_timezone_obj ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* php_timezone_obj_from_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_timezone_to_string (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_array_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_str_update (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_std_get_properties (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HashTable *date_object_get_debug_info_timezone(zend_object *object, int *is_temp) /* {{{ */
{
	HashTable *ht, *props;
	zval zv;
	php_timezone_obj *tzobj;

	tzobj = php_timezone_obj_from_obj(object);
	props = zend_std_get_properties(object);

	*is_temp = 1;
	ht = zend_array_dup(props);

	ZVAL_LONG(&zv, tzobj->type);
	zend_hash_str_update(ht, "timezone_type", sizeof("timezone_type")-1, &zv);

	php_timezone_to_string(tzobj, &zv);
	zend_hash_str_update(ht, "timezone", sizeof("timezone")-1, &zv);

	return ht;
}