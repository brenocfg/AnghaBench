#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ zend_class_entry ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_ERROR ; 
 int FAILURE ; 
 int SUCCESS ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 scalar_t__ instanceof_function (TYPE_1__*,TYPE_4__*) ; 
 TYPE_4__* zend_ce_error ; 
 TYPE_4__* zend_ce_exception ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zend_implement_throwable(zend_class_entry *interface, zend_class_entry *class_type)
{
	if (instanceof_function(class_type, zend_ce_exception) || instanceof_function(class_type, zend_ce_error)) {
		return SUCCESS;
	}
	zend_error_noreturn(E_ERROR, "Class %s cannot implement interface %s, extend %s or %s instead",
		ZSTR_VAL(class_type->name),
		ZSTR_VAL(interface->name),
		ZSTR_VAL(zend_ce_exception->name),
		ZSTR_VAL(zend_ce_error->name));
	return FAILURE;
}