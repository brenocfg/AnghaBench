#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_DELREF_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_property_zval (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_soap_fault (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_soap_fault_ex(zval *fault, zval *obj, char *fault_code, char *fault_string, char *fault_actor, zval *fault_detail) /* {{{ */
{
	ZVAL_NULL(fault);
	set_soap_fault(fault, NULL, fault_code, fault_string, fault_actor, fault_detail, NULL);
	add_property_zval(obj, "__soap_fault", fault);
	Z_DELREF_P(fault);
}