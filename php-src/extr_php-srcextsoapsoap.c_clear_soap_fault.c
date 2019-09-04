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
 scalar_t__ IS_OBJECT ; 
 int /*<<< orphan*/  Z_OBJPROP_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_str_del (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void clear_soap_fault(zval *obj) /* {{{ */
{
	if (obj != NULL && Z_TYPE_P(obj) == IS_OBJECT) {
		zend_hash_str_del(Z_OBJPROP_P(obj), "__soap_fault", sizeof("__soap_fault")-1);
	}
}