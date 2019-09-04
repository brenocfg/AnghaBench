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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_object ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  php_com_throw_exception (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static zval *saproxy_property_write(zend_object *object, zend_string *member, zval *value, void **cache_slot)
{
	php_com_throw_exception(E_INVALIDARG, "safearray has no properties");
	return value;
}