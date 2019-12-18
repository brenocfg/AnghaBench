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
typedef  int zend_prop_purpose ;
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_4__ {int /*<<< orphan*/  type; int /*<<< orphan*/  initialized; } ;
typedef  TYPE_1__ php_timezone_obj ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
#define  ZEND_PROP_PURPOSE_ARRAY_CAST 132 
#define  ZEND_PROP_PURPOSE_DEBUG 131 
#define  ZEND_PROP_PURPOSE_JSON 130 
#define  ZEND_PROP_PURPOSE_SERIALIZE 129 
#define  ZEND_PROP_PURPOSE_VAR_EXPORT 128 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* php_timezone_obj_from_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_timezone_to_string (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_array_dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_str_update (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_std_get_properties (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_std_get_properties_for (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static HashTable *date_object_get_properties_for_timezone(zend_object *object, zend_prop_purpose purpose) /* {{{ */
{
	HashTable *props;
	zval zv;
	php_timezone_obj *tzobj;

	switch (purpose) {
		case ZEND_PROP_PURPOSE_DEBUG:
		case ZEND_PROP_PURPOSE_SERIALIZE:
		case ZEND_PROP_PURPOSE_VAR_EXPORT:
		case ZEND_PROP_PURPOSE_JSON:
		case ZEND_PROP_PURPOSE_ARRAY_CAST:
			break;
		default:
			return zend_std_get_properties_for(object, purpose);
	}

	tzobj = php_timezone_obj_from_obj(object);
	props = zend_array_dup(zend_std_get_properties(object));
	if (!tzobj->initialized) {
		return props;
	}

	ZVAL_LONG(&zv, tzobj->type);
	zend_hash_str_update(props, "timezone_type", sizeof("timezone_type")-1, &zv);

	php_timezone_to_string(tzobj, &zv);
	zend_hash_str_update(props, "timezone", sizeof("timezone")-1, &zv);

	return props;
}