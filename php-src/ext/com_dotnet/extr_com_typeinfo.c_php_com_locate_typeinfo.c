#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  v; int /*<<< orphan*/ * typeinfo; } ;
typedef  TYPE_1__ php_com_dotnet_object ;
struct TYPE_7__ {int cImplTypes; } ;
typedef  TYPE_2__ TYPEATTR ;
typedef  int /*<<< orphan*/  OLECHAR ;
typedef  int /*<<< orphan*/  MEMBERID ;
typedef  int /*<<< orphan*/  ITypeLib ;
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  int /*<<< orphan*/  IProvideClassInfo2 ;
typedef  int /*<<< orphan*/  IProvideClassInfo ;
typedef  int /*<<< orphan*/  HREFTYPE ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 int /*<<< orphan*/  CLSIDFromProgID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  CP_THREAD_ACP ; 
 int /*<<< orphan*/  E_WARNING ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GUIDKIND_DEFAULT_SOURCE_DISP_IID ; 
 int /*<<< orphan*/  IDispatch_GetTypeInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IDispatch_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IProvideClassInfo ; 
 int /*<<< orphan*/  IID_IProvideClassInfo2 ; 
 int IMPLTYPEFLAG_FDEFAULT ; 
 int IMPLTYPEFLAG_FSOURCE ; 
 int /*<<< orphan*/  IProvideClassInfo2_GetGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IProvideClassInfo2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IProvideClassInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeInfo_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeInfo_GetContainingTypeLib (int /*<<< orphan*/ *,int /*<<< orphan*/ **,unsigned int*) ; 
 int /*<<< orphan*/  ITypeInfo_GetImplTypeFlags (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  ITypeInfo_GetRefTypeInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITypeInfo_GetRefTypeOfImplType (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeInfo_GetTypeAttr (int /*<<< orphan*/ *,TYPE_2__**) ; 
 int /*<<< orphan*/  ITypeInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeInfo_ReleaseTypeAttr (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ITypeLib_FindName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,unsigned short*) ; 
 int /*<<< orphan*/  ITypeLib_GetTypeInfoOfGuid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITypeLib_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 int SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_DISPATCH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * php_com_load_typelib (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * php_com_string_to_olestring (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

ITypeInfo *php_com_locate_typeinfo(char *typelibname, php_com_dotnet_object *obj, char *dispname, int sink)
{
	ITypeInfo *typeinfo = NULL;
	ITypeLib *typelib = NULL;
	int gotguid = 0;
	GUID iid;

	if (obj) {
		if (dispname == NULL && sink) {
			IProvideClassInfo2 *pci2;
			IProvideClassInfo *pci;

			if (SUCCEEDED(IDispatch_QueryInterface(V_DISPATCH(&obj->v), &IID_IProvideClassInfo2, (void**)&pci2))) {
				gotguid = SUCCEEDED(IProvideClassInfo2_GetGUID(pci2, GUIDKIND_DEFAULT_SOURCE_DISP_IID, &iid));
				IProvideClassInfo2_Release(pci2);
			}
			if (!gotguid && SUCCEEDED(IDispatch_QueryInterface(V_DISPATCH(&obj->v), &IID_IProvideClassInfo, (void**)&pci))) {
				/* examine the available interfaces */
				/* TODO: write some code here */
				php_error_docref(NULL, E_WARNING, "IProvideClassInfo: this code not yet written!");
				IProvideClassInfo_Release(pci);
			}
		} else if (dispname == NULL) {
			if (obj->typeinfo) {
				ITypeInfo_AddRef(obj->typeinfo);
				return obj->typeinfo;
			} else {
				IDispatch_GetTypeInfo(V_DISPATCH(&obj->v), 0, LANG_NEUTRAL, &typeinfo);
				if (typeinfo) {
					return typeinfo;
				}
			}
		} else if (dispname && obj->typeinfo) {
			unsigned int idx;
			/* get the library from the object; the rest will be dealt with later */
			ITypeInfo_GetContainingTypeLib(obj->typeinfo, &typelib, &idx);
		} else if (typelibname == NULL) {
			IDispatch_GetTypeInfo(V_DISPATCH(&obj->v), 0, LANG_NEUTRAL, &typeinfo);
			if (dispname) {
				unsigned int idx;
				/* get the library from the object; the rest will be dealt with later */
				ITypeInfo_GetContainingTypeLib(typeinfo, &typelib, &idx);

				if (typelib) {
					ITypeInfo_Release(typeinfo);
					typeinfo = NULL;
				}
			}
		}
	} else if (typelibname) {
		/* Fetch the typelibrary and use that to look things up */
		typelib = php_com_load_typelib(typelibname, CP_THREAD_ACP);
	}

	if (!gotguid && dispname && typelib) {
		unsigned short cfound;
		MEMBERID memid;
		OLECHAR *olename = php_com_string_to_olestring(dispname, strlen(dispname), CP_ACP);

		cfound = 1;
		if (FAILED(ITypeLib_FindName(typelib, olename, 0, &typeinfo, &memid, &cfound)) || cfound == 0) {
			CLSID coclass;
			ITypeInfo *coinfo;

			/* assume that it might be a progid instead */
			if (SUCCEEDED(CLSIDFromProgID(olename, &coclass)) &&
					SUCCEEDED(ITypeLib_GetTypeInfoOfGuid(typelib, &coclass, &coinfo))) {

				/* enumerate implemented interfaces and pick the one as indicated by sink */
				TYPEATTR *attr;
				int i;

				ITypeInfo_GetTypeAttr(coinfo, &attr);

				for (i = 0; i < attr->cImplTypes; i++) {
					HREFTYPE rt;
					int tf;

					if (FAILED(ITypeInfo_GetImplTypeFlags(coinfo, i, &tf))) {
						continue;
					}

					if ((sink && tf == (IMPLTYPEFLAG_FSOURCE|IMPLTYPEFLAG_FDEFAULT)) ||
						(!sink && (tf & IMPLTYPEFLAG_FSOURCE) == 0)) {

						/* flags match what we are looking for */

						if (SUCCEEDED(ITypeInfo_GetRefTypeOfImplType(coinfo, i, &rt)))
							if (SUCCEEDED(ITypeInfo_GetRefTypeInfo(coinfo, rt, &typeinfo)))
								break;

					}
				}

				ITypeInfo_ReleaseTypeAttr(coinfo, attr);
				ITypeInfo_Release(coinfo);
			}
		}


		efree(olename);
	} else if (gotguid) {
		ITypeLib_GetTypeInfoOfGuid(typelib, &iid, &typeinfo);
	}

	if (typelib) {
		ITypeLib_Release(typelib);
	}

	return typeinfo;
}