#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int ce_flags; scalar_t__ (* interface_gets_implemented ) (TYPE_1__*,TYPE_1__*) ;int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ zend_class_entry ;

/* Variables and functions */
 int /*<<< orphan*/  E_CORE_ERROR ; 
 scalar_t__ FAILURE ; 
 int ZEND_ACC_INTERFACE ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void do_implement_interface(zend_class_entry *ce, zend_class_entry *iface) /* {{{ */
{
	if (!(ce->ce_flags & ZEND_ACC_INTERFACE) && iface->interface_gets_implemented && iface->interface_gets_implemented(iface, ce) == FAILURE) {
		zend_error_noreturn(E_CORE_ERROR, "Class %s could not implement interface %s", ZSTR_VAL(ce->name), ZSTR_VAL(iface->name));
	}
	/* This should be prevented by the class lookup logic. */
	ZEND_ASSERT(ce != iface);
}