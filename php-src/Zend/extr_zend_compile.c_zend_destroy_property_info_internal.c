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
struct TYPE_4__ {int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ zend_property_info ;

/* Variables and functions */
 TYPE_1__* Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zend_type_release (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void zend_destroy_property_info_internal(zval *zv) /* {{{ */
{
	zend_property_info *property_info = Z_PTR_P(zv);

	zend_string_release_ex(property_info->name, 1);
	zend_type_release(property_info->type, /* persistent */ 1);
	free(property_info);
}