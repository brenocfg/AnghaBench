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
struct TYPE_3__ {scalar_t__ id_of_name_cache; int /*<<< orphan*/  v; int /*<<< orphan*/ * typeinfo; int /*<<< orphan*/  code_page; } ;
typedef  TYPE_1__ php_com_dotnet_object ;
typedef  int /*<<< orphan*/  OLECHAR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DISPID ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_HASHTABLE (scalar_t__) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDispatch_GetIDsOfNames (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  IID_NULL ; 
 int /*<<< orphan*/  ITypeInfo_GetIDsOfNames (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,scalar_t__*) ; 
 int /*<<< orphan*/  ITypeInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOCALE_SYSTEM_DEFAULT ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  V_DISPATCH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ Z_LVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * php_com_string_to_olestring (char*,size_t,int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  zend_hash_init (scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_hash_str_find (scalar_t__,char*,size_t) ; 
 int /*<<< orphan*/  zend_hash_str_update (scalar_t__,char*,size_t,int /*<<< orphan*/ *) ; 

HRESULT php_com_get_id_of_name(php_com_dotnet_object *obj, char *name,
		size_t namelen, DISPID *dispid)
{
	OLECHAR *olename;
	HRESULT hr;
	zval *tmp;

	if (namelen == -1) {
		namelen = strlen(name);
	}

	if (obj->id_of_name_cache && NULL != (tmp = zend_hash_str_find(obj->id_of_name_cache, name, namelen))) {
		*dispid = (DISPID)Z_LVAL_P(tmp);
		return S_OK;
	}

	olename = php_com_string_to_olestring(name, namelen, obj->code_page);

	if (obj->typeinfo) {
		hr = ITypeInfo_GetIDsOfNames(obj->typeinfo, &olename, 1, dispid);
		if (FAILED(hr)) {
			hr = IDispatch_GetIDsOfNames(V_DISPATCH(&obj->v), &IID_NULL, &olename, 1, LOCALE_SYSTEM_DEFAULT, dispid);
			if (SUCCEEDED(hr)) {
				/* fall back on IDispatch direct */
				ITypeInfo_Release(obj->typeinfo);
				obj->typeinfo = NULL;
			}
		}
	} else {
		hr = IDispatch_GetIDsOfNames(V_DISPATCH(&obj->v), &IID_NULL, &olename, 1, LOCALE_SYSTEM_DEFAULT, dispid);
	}
	efree(olename);

	if (SUCCEEDED(hr)) {
		zval tmp;

		/* cache the mapping */
		if (!obj->id_of_name_cache) {
			ALLOC_HASHTABLE(obj->id_of_name_cache);
			zend_hash_init(obj->id_of_name_cache, 2, NULL, NULL, 0);
		}
		ZVAL_LONG(&tmp, *dispid);
		zend_hash_str_update(obj->id_of_name_cache, name, namelen, &tmp);
	}

	return hr;
}