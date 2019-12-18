#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_17__ {scalar_t__ vt; TYPE_4__* lptdesc; } ;
struct TYPE_15__ {int wParamFlags; } ;
struct TYPE_20__ {TYPE_5__ tdesc; TYPE_3__ paramdesc; } ;
struct TYPE_13__ {scalar_t__ vt; } ;
struct TYPE_14__ {TYPE_1__ tdesc; } ;
struct TYPE_19__ {int invkind; scalar_t__ memid; int cParams; TYPE_8__* lprgelemdescParam; TYPE_2__ elemdescFunc; } ;
struct TYPE_18__ {scalar_t__ typekind; int cFuncs; int /*<<< orphan*/  guid; } ;
struct TYPE_16__ {scalar_t__ vt; } ;
typedef  TYPE_6__ TYPEATTR ;
typedef  int /*<<< orphan*/  OLECHAR ;
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  int /*<<< orphan*/  HashTable ;
typedef  int /*<<< orphan*/  GUID ;
typedef  TYPE_7__ FUNCDESC ;
typedef  TYPE_8__ ELEMDESC ;
typedef  scalar_t__ DISPID ;
typedef  char BSTR ;

/* Variables and functions */
 int DISPATCH_PROPERTYGET ; 
 int DISPATCH_PROPERTYPUT ; 
 int /*<<< orphan*/  E_WARNING ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITypeInfo_GetDocumentation (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeInfo_GetFuncDesc (int /*<<< orphan*/ *,int,TYPE_7__**) ; 
 int /*<<< orphan*/  ITypeInfo_GetNames (int /*<<< orphan*/ *,scalar_t__,char*,int,unsigned int*) ; 
 int /*<<< orphan*/  ITypeInfo_GetTypeAttr (int /*<<< orphan*/ *,TYPE_6__**) ; 
 int /*<<< orphan*/  ITypeInfo_ReleaseFuncDesc (int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  ITypeInfo_ReleaseTypeAttr (int /*<<< orphan*/ *,TYPE_6__*) ; 
 scalar_t__ MEMBERID_NIL ; 
 int PARAMFLAG_FIN ; 
 int PARAMFLAG_FOUT ; 
 int /*<<< orphan*/  SysFreeString (char) ; 
 scalar_t__ TKIND_DISPATCH ; 
 scalar_t__ VT_PTR ; 
 scalar_t__ VT_VOID ; 
 int /*<<< orphan*/  ZVAL_PTR_DTOR ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 char* php_com_olestring_to_string (char,size_t*,int) ; 
 char* php_com_string_from_clsid (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  php_printf (char*,...) ; 
 scalar_t__ safe_emalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vt_to_string (scalar_t__) ; 
 int /*<<< orphan*/  zend_error (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  zend_hash_index_update (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_str_tolower (char*,size_t) ; 

int php_com_process_typeinfo(ITypeInfo *typeinfo, HashTable *id_to_name, int printdef, GUID *guid, int codepage)
{
	TYPEATTR *attr;
	FUNCDESC *func;
	int i;
	OLECHAR *olename;
	char *ansiname = NULL;
	size_t ansinamelen;
	int ret = 0;

	if (FAILED(ITypeInfo_GetTypeAttr(typeinfo, &attr))) {
		return 0;
	}

	/* verify that it is suitable */
	if (id_to_name == NULL || attr->typekind == TKIND_DISPATCH) {

		if (guid) {
			memcpy(guid, &attr->guid, sizeof(GUID));
		}

		if (printdef) {
			char *guidstring;

			ITypeInfo_GetDocumentation(typeinfo, MEMBERID_NIL, &olename, NULL, NULL, NULL);
			ansiname = php_com_olestring_to_string(olename, &ansinamelen, codepage);
			SysFreeString(olename);

			guidstring = php_com_string_from_clsid(&attr->guid, codepage);
			php_printf("class %s { /* GUID=%s */\n", ansiname, guidstring);
			efree(guidstring);

			efree(ansiname);
		}

		if (id_to_name) {
			zend_hash_init(id_to_name, 0, NULL, ZVAL_PTR_DTOR, 0);
		}

		/* So we've got the dispatch interface; lets list the event methods */
		for (i = 0; i < attr->cFuncs; i++) {
			zval tmp;
			DISPID lastid = 0;	/* for props */
			int isprop;

			if (FAILED(ITypeInfo_GetFuncDesc(typeinfo, i, &func)))
				break;

			isprop = (func->invkind & DISPATCH_PROPERTYGET || func->invkind & DISPATCH_PROPERTYPUT);

			if (!isprop || lastid != func->memid) {

				lastid = func->memid;

				ITypeInfo_GetDocumentation(typeinfo, func->memid, &olename, NULL, NULL, NULL);
				ansiname = php_com_olestring_to_string(olename, &ansinamelen, codepage);
				SysFreeString(olename);

				if (printdef) {
					int j;
					char *funcdesc;
					size_t funcdesclen;
					unsigned int cnames = 0;
					BSTR *names;

					names = (BSTR*)safe_emalloc((func->cParams + 1), sizeof(BSTR), 0);

					ITypeInfo_GetNames(typeinfo, func->memid, names, func->cParams + 1, &cnames);
					/* first element is the function name */
					SysFreeString(names[0]);

					php_printf("\t/* DISPID=%d */\n", func->memid);

					if (func->elemdescFunc.tdesc.vt != VT_VOID) {
						php_printf("\t/* %s [%d] */\n",
								vt_to_string(func->elemdescFunc.tdesc.vt),
								func->elemdescFunc.tdesc.vt
								);
					}

					if (isprop) {

						ITypeInfo_GetDocumentation(typeinfo, func->memid, NULL, &olename, NULL, NULL);
						if (olename) {
							funcdesc = php_com_olestring_to_string(olename, &funcdesclen, codepage);
							SysFreeString(olename);
							php_printf("\t/* %s */\n", funcdesc);
							efree(funcdesc);
						}

						php_printf("\tvar $%s;\n\n", ansiname);

					} else {
						/* a function */

						php_printf("\tfunction %s(\n", ansiname);

						for (j = 0; j < func->cParams; j++) {
							ELEMDESC *elem = &func->lprgelemdescParam[j];

							php_printf("\t\t/* %s [%d] ", vt_to_string(elem->tdesc.vt), elem->tdesc.vt);

							if (elem->paramdesc.wParamFlags & PARAMFLAG_FIN)
								php_printf("[in]");
							if (elem->paramdesc.wParamFlags & PARAMFLAG_FOUT)
								php_printf("[out]");

							if (elem->tdesc.vt == VT_PTR) {
								/* what does it point to ? */
								php_printf(" --> %s [%d] ",
										vt_to_string(elem->tdesc.lptdesc->vt),
										elem->tdesc.lptdesc->vt
										);
							}

							/* when we handle prop put and get, this will look nicer */
							if (j+1 < (int)cnames) {
								funcdesc = php_com_olestring_to_string(names[j+1], &funcdesclen, codepage);
								SysFreeString(names[j+1]);
							} else {
								funcdesc = "???";
							}

							php_printf(" */ %s%s%c\n",
									elem->tdesc.vt == VT_PTR ? "&$" : "$",
									funcdesc,
									j == func->cParams - 1 ? ' ' : ','
									);

							if (j+1 < (int)cnames) {
								efree(funcdesc);
							}
						}

						php_printf("\t\t)\n\t{\n");

						ITypeInfo_GetDocumentation(typeinfo, func->memid, NULL, &olename, NULL, NULL);
						if (olename) {
							funcdesc = php_com_olestring_to_string(olename, &funcdesclen, codepage);
							SysFreeString(olename);
							php_printf("\t\t/* %s */\n", funcdesc);
							efree(funcdesc);
						}

						php_printf("\t}\n");
					}

					efree(names);
				}

				if (id_to_name) {
					zend_str_tolower(ansiname, ansinamelen);
					ZVAL_STRINGL(&tmp, ansiname, ansinamelen);
					zend_hash_index_update(id_to_name, func->memid, &tmp);
					// TODO: avoid reallocation???
					efree(ansiname);
				}
			}
			ITypeInfo_ReleaseFuncDesc(typeinfo, func);
		}

		if (printdef) {
			php_printf("}\n");
		}

		ret = 1;
	} else {
		zend_error(E_WARNING, "That's not a dispatchable interface!! type kind = %08x", attr->typekind);
	}

	ITypeInfo_ReleaseTypeAttr(typeinfo, attr);

	return ret;
}