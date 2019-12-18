#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; } ;
typedef  TYPE_1__ zend_class_entry ;

/* Variables and functions */
 int /*<<< orphan*/  E_ERROR ; 
 int SUCCESS ; 
 scalar_t__ ZEND_USER_CLASS ; 
 int /*<<< orphan*/  date_ce_date ; 
 int /*<<< orphan*/  date_ce_immutable ; 
 int /*<<< orphan*/  instanceof_function (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_error (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int implement_date_interface_handler(zend_class_entry *interface, zend_class_entry *implementor) /* {{{ */
{
	if (implementor->type == ZEND_USER_CLASS &&
		!instanceof_function(implementor, date_ce_date) &&
		!instanceof_function(implementor, date_ce_immutable)
	) {
		zend_error(E_ERROR, "DateTimeInterface can't be implemented by user classes");
	}

	return SUCCESS;
}