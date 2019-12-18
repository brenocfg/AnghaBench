#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_5__ {int /*<<< orphan*/ * properties; } ;
struct TYPE_6__ {TYPE_1__ std; } ;
typedef  TYPE_2__ spl_array_object ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_COMPARE_OBJECTS_FALLBACK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* Z_SPLARRAY_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * spl_array_get_hash_table (TYPE_2__*) ; 
 int zend_compare_symbol_tables (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zend_std_compare_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int spl_array_compare_objects(zval *o1, zval *o2) /* {{{ */
{
	HashTable			*ht1,
						*ht2;
	spl_array_object	*intern1,
						*intern2;
	int					result	= 0;

	ZEND_COMPARE_OBJECTS_FALLBACK(o1, o2);

	intern1	= Z_SPLARRAY_P(o1);
	intern2	= Z_SPLARRAY_P(o2);
	ht1		= spl_array_get_hash_table(intern1);
	ht2		= spl_array_get_hash_table(intern2);

	result = zend_compare_symbol_tables(ht1, ht2);
	/* if we just compared std.properties, don't do it again */
	if (result == 0 &&
			!(ht1 == intern1->std.properties && ht2 == intern2->std.properties)) {
		result = zend_std_compare_objects(o1, o2);
	}
	return result;
}