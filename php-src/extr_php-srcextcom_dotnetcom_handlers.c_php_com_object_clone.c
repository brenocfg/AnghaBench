#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_4__ {scalar_t__ typeinfo; int /*<<< orphan*/  v; } ;
typedef  TYPE_1__ php_com_dotnet_object ;

/* Variables and functions */
 int /*<<< orphan*/  ITypeInfo_AddRef (scalar_t__) ; 
 int /*<<< orphan*/  VariantCopyInd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 scalar_t__ emalloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 

zend_object* php_com_object_clone(zend_object *object)
{
	php_com_dotnet_object *cloneobj, *origobject;

	origobject = (php_com_dotnet_object*) object;
	cloneobj = (php_com_dotnet_object*)emalloc(sizeof(php_com_dotnet_object));

	memcpy(cloneobj, origobject, sizeof(*cloneobj));

	/* VariantCopy will perform VariantClear; we don't want to clobber
	 * the IDispatch that we memcpy'd, so we init a new variant in the
	 * clone structure */
	VariantInit(&cloneobj->v);
	/* We use the Indirection-following version of the API since we
	 * want to clone as much as possible */
	VariantCopyInd(&cloneobj->v, &origobject->v);

	if (cloneobj->typeinfo) {
		ITypeInfo_AddRef(cloneobj->typeinfo);
	}

	return (zend_object*)cloneobj;
}