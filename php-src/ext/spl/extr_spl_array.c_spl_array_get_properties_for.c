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
typedef  int zend_prop_purpose ;
typedef  int /*<<< orphan*/  zend_object ;
typedef  int zend_bool ;
struct TYPE_4__ {int ar_flags; } ;
typedef  TYPE_1__ spl_array_object ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  GC_ADDREF (int /*<<< orphan*/ *) ; 
 int SPL_ARRAY_STD_PROP_LIST ; 
#define  ZEND_PROP_PURPOSE_ARRAY_CAST 130 
#define  ZEND_PROP_PURPOSE_JSON 129 
#define  ZEND_PROP_PURPOSE_VAR_EXPORT 128 
 TYPE_1__* spl_array_from_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * spl_array_get_hash_table (TYPE_1__*) ; 
 int /*<<< orphan*/ * zend_array_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_std_get_properties_for (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static HashTable *spl_array_get_properties_for(zend_object *object, zend_prop_purpose purpose) /* {{{ */
{
	spl_array_object *intern = spl_array_from_obj(object);
	HashTable *ht;
	zend_bool dup;

	if (intern->ar_flags & SPL_ARRAY_STD_PROP_LIST) {
		return zend_std_get_properties_for(object, purpose);
	}

	/* We are supposed to be the only owner of the internal hashtable.
	 * The "dup" flag decides whether this is a "long-term" use where
	 * we need to duplicate, or a "temporary" one, where we can expect
	 * that no operations on the ArrayObject will be performed in the
	 * meantime. */
	switch (purpose) {
		case ZEND_PROP_PURPOSE_ARRAY_CAST:
			dup = 1;
			break;
		case ZEND_PROP_PURPOSE_VAR_EXPORT:
		case ZEND_PROP_PURPOSE_JSON:
			dup = 0;
			break;
		default:
			return zend_std_get_properties_for(object, purpose);
	}

	ht = spl_array_get_hash_table(intern);
	if (dup) {
		ht = zend_array_dup(ht);
	} else {
		GC_ADDREF(ht);
	}
	return ht;
}