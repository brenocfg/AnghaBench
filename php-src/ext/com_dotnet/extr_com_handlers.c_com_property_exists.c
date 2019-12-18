#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_3__ {int /*<<< orphan*/  v; } ;
typedef  TYPE_1__ php_com_dotnet_object ;
typedef  int /*<<< orphan*/  DISPID ;

/* Variables and functions */
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 scalar_t__ VT_DISPATCH ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_com_get_id_of_name (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int com_property_exists(zend_object *object, zend_string *member, int check_empty, void **cache_slot)
{
	DISPID dispid;
	php_com_dotnet_object *obj;

	obj = (php_com_dotnet_object*) object;

	if (V_VT(&obj->v) == VT_DISPATCH) {
		if (SUCCEEDED(php_com_get_id_of_name(obj, ZSTR_VAL(member), ZSTR_LEN(member), &dispid))) {
			/* TODO: distinguish between property and method! */
			return 1;
		}
	} else {
		/* TODO: check for safearray */
	}

	return 0;
}