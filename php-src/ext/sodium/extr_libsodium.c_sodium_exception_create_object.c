#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object ;
typedef  int /*<<< orphan*/  zend_class_entry ;
struct TYPE_2__ {int /*<<< orphan*/ * (* create_object ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  sodium_remove_param_values_from_backtrace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *) ; 
 TYPE_1__* zend_ce_exception ; 

__attribute__((used)) static zend_object *sodium_exception_create_object(zend_class_entry *ce) {
	zend_object *obj = zend_ce_exception->create_object(ce);
	sodium_remove_param_values_from_backtrace(obj);
	return obj;
}