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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_3__ {int /*<<< orphan*/  code_page; int /*<<< orphan*/  v; } ;
typedef  TYPE_1__ php_com_dotnet_object ;
typedef  scalar_t__ VARTYPE ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int DISPATCH_METHOD ; 
 int DISPATCH_PROPERTYGET ; 
 int /*<<< orphan*/  DISPID_VALUE ; 
#define  IS_DOUBLE 134 
#define  IS_FALSE 133 
#define  IS_LONG 132 
#define  IS_STRING 131 
#define  IS_TRUE 130 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ VT_BOOL ; 
 scalar_t__ VT_BSTR ; 
 scalar_t__ VT_DISPATCH ; 
 scalar_t__ VT_EMPTY ; 
 scalar_t__ VT_INT ; 
 scalar_t__ VT_R8 ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantChangeType (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
#define  _IS_BOOL 129 
#define  _IS_NUMBER 128 
 scalar_t__ php_com_do_invoke_by_id (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_com_zval_from_variant (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zend_std_cast_object_tostring (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int com_object_cast(zend_object *readobj, zval *writeobj, int type)
{
	php_com_dotnet_object *obj;
	VARIANT v;
	VARTYPE vt = VT_EMPTY;
	HRESULT res = S_OK;

	obj = (php_com_dotnet_object*) readobj;
	ZVAL_NULL(writeobj);
	VariantInit(&v);

	if (V_VT(&obj->v) == VT_DISPATCH) {
		if (SUCCESS != php_com_do_invoke_by_id(obj, DISPID_VALUE,
				DISPATCH_METHOD|DISPATCH_PROPERTYGET, &v, 0, NULL, 1, 0)) {
			VariantCopy(&v, &obj->v);
		}
	} else {
		VariantCopy(&v, &obj->v);
	}

	switch(type) {
		case IS_LONG:
		case _IS_NUMBER:
			vt = VT_INT;
			break;
		case IS_DOUBLE:
			vt = VT_R8;
			break;
		case IS_FALSE:
		case IS_TRUE:
		case _IS_BOOL:
			vt = VT_BOOL;
			break;
		case IS_STRING:
			vt = VT_BSTR;
			break;
		default:
			;
	}

	if (vt != VT_EMPTY && vt != V_VT(&v)) {
		res = VariantChangeType(&v, &v, 0, vt);
	}

	if (SUCCEEDED(res)) {
		php_com_zval_from_variant(writeobj, &v, obj->code_page);
	}

	VariantClear(&v);

	if (SUCCEEDED(res)) {
		return SUCCESS;
	}

	return zend_std_cast_object_tostring(readobj, writeobj, type);
}