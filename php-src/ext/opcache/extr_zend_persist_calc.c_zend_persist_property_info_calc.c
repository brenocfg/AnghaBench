#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_7__ {scalar_t__ doc_comment; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ zend_property_info ;
struct TYPE_8__ {scalar_t__ save_comments; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_INTERNED_STRING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADD_SIZE_EX (int) ; 
 int /*<<< orphan*/  ADD_STRING (scalar_t__) ; 
 TYPE_6__ ZCG (int /*<<< orphan*/ ) ; 
 TYPE_1__* Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  accel_directives ; 
 int /*<<< orphan*/  zend_persist_type_calc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_shared_alloc_get_xlat_entry (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_shared_alloc_register_xlat_entry (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static void zend_persist_property_info_calc(zval *zv)
{
	zend_property_info *prop = Z_PTR_P(zv);

	if (!zend_shared_alloc_get_xlat_entry(prop)) {
		zend_shared_alloc_register_xlat_entry(prop, prop);
		ADD_SIZE_EX(sizeof(zend_property_info));
		ADD_INTERNED_STRING(prop->name);
		zend_persist_type_calc(&prop->type);
		if (ZCG(accel_directives).save_comments && prop->doc_comment) {
			ADD_STRING(prop->doc_comment);
		}
	}
}