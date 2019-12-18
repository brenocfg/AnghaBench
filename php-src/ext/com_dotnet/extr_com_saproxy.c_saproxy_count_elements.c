#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object ;
typedef  scalar_t__ zend_long ;
struct TYPE_4__ {int /*<<< orphan*/  dimensions; TYPE_1__* obj; } ;
typedef  TYPE_2__ php_com_saproxy ;
struct TYPE_3__ {int /*<<< orphan*/  v; } ;
typedef  scalar_t__ LONG ;

/* Variables and functions */
 int FAILURE ; 
 int SUCCESS ; 
 int /*<<< orphan*/  SafeArrayGetLBound (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  SafeArrayGetUBound (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  V_ARRAY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_ISARRAY (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int saproxy_count_elements(zend_object *object, zend_long *count)
{
	php_com_saproxy *proxy = (php_com_saproxy*) object;
	LONG ubound, lbound;

	if (!V_ISARRAY(&proxy->obj->v)) {
		return FAILURE;
	}

	SafeArrayGetLBound(V_ARRAY(&proxy->obj->v), proxy->dimensions, &lbound);
	SafeArrayGetUBound(V_ARRAY(&proxy->obj->v), proxy->dimensions, &ubound);

	*count = ubound - lbound + 1;

	return SUCCESS;
}