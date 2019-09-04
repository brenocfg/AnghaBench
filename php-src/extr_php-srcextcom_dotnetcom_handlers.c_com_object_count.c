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
typedef  scalar_t__ zend_long ;
struct TYPE_2__ {int /*<<< orphan*/  v; } ;
typedef  TYPE_1__ php_com_dotnet_object ;
typedef  scalar_t__ LONG ;

/* Variables and functions */
 int FAILURE ; 
 int SUCCESS ; 
 int /*<<< orphan*/  SafeArrayGetLBound (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  SafeArrayGetUBound (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  V_ARRAY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_ISARRAY (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int com_object_count(zend_object *object, zend_long *count)
{
	php_com_dotnet_object *obj;
	LONG ubound = 0, lbound = 0;

	obj = (php_com_dotnet_object*) object;

	if (!V_ISARRAY(&obj->v)) {
		return FAILURE;
	}

	SafeArrayGetLBound(V_ARRAY(&obj->v), 1, &lbound);
	SafeArrayGetUBound(V_ARRAY(&obj->v), 1, &ubound);

	*count = ubound - lbound + 1;

	return SUCCESS;
}