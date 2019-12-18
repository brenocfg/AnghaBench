#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_17__ ;
typedef  struct TYPE_19__   TYPE_15__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_type ;
struct TYPE_23__ {int /*<<< orphan*/  len; int /*<<< orphan*/  val; } ;
typedef  TYPE_3__ zend_string ;
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_24__ {int num_args; int /*<<< orphan*/  function_name; TYPE_15__* arg_info; int /*<<< orphan*/  handler; int /*<<< orphan*/  fn_flags; int /*<<< orphan*/  scope; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ zend_internal_function ;
typedef  int /*<<< orphan*/  zend_function ;
typedef  int zend_bool ;
typedef  int /*<<< orphan*/  zend_arg_info ;
struct TYPE_25__ {int /*<<< orphan*/ * method_cache; int /*<<< orphan*/  code_page; scalar_t__ typeinfo; int /*<<< orphan*/  ce; int /*<<< orphan*/  v; } ;
typedef  TYPE_5__ php_com_dotnet_object ;
typedef  int /*<<< orphan*/  f ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_26__ {int /*<<< orphan*/ * lptcomp; int /*<<< orphan*/  lpvardesc; TYPE_17__* lpfuncdesc; } ;
struct TYPE_21__ {int wParamFlags; } ;
struct TYPE_22__ {TYPE_1__ paramdesc; } ;
struct TYPE_20__ {int cParams; TYPE_2__* lprgelemdescParam; } ;
struct TYPE_19__ {int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  OLECHAR ;
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  int /*<<< orphan*/  ITypeComp ;
typedef  int /*<<< orphan*/  DISPID ;
typedef  int DESCKIND ;
typedef  TYPE_6__ BINDPTR ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_HASHTABLE (int /*<<< orphan*/ *) ; 
#define  DESCKIND_FUNCDESC 131 
#define  DESCKIND_NONE 130 
#define  DESCKIND_TYPECOMP 129 
#define  DESCKIND_VARDESC 128 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INVOKE_FUNC ; 
 int /*<<< orphan*/  ITypeComp_Bind (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,TYPE_6__*) ; 
 int /*<<< orphan*/  ITypeComp_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeInfo_GetTypeComp (scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITypeInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeInfo_ReleaseFuncDesc (int /*<<< orphan*/ *,TYPE_17__*) ; 
 int /*<<< orphan*/  ITypeInfo_ReleaseVarDesc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LHashValOfNameSys (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOCALE_SYSTEM_DEFAULT ; 
 int PARAMFLAG_FOUT ; 
 int /*<<< orphan*/  PHP_FN (int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_WIN32 ; 
 scalar_t__ VT_DISPATCH ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZEND_ACC_CALL_VIA_HANDLER ; 
 int /*<<< orphan*/  ZEND_INTERNAL_FUNCTION ; 
 int /*<<< orphan*/  ZEND_TYPE_INIT_NONE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ZEND_ARG_INFO_FLAGS (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  com_method_handler ; 
 TYPE_15__* ecalloc (int,int) ; 
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * emalloc (int) ; 
 int /*<<< orphan*/  function_dtor ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  php_com_get_id_of_name (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * php_com_string_to_olestring (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* zend_hash_find_ptr (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  zend_hash_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_update_mem (int /*<<< orphan*/ *,TYPE_3__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  zend_set_function_arg_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_addref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_copy (TYPE_3__*) ; 

__attribute__((used)) static zend_function *com_method_get(zend_object **object_ptr, zend_string *name, const zval *key)
{
	zend_internal_function f, *fptr = NULL;
	zend_function *func;
	DISPID dummy;
	php_com_dotnet_object *obj = (php_com_dotnet_object*)*object_ptr;

	if (V_VT(&obj->v) != VT_DISPATCH) {
		return NULL;
	}

	if (FAILED(php_com_get_id_of_name(obj, name->val, name->len, &dummy))) {
		return NULL;
	}

	/* check cache */
	if (obj->method_cache == NULL || NULL == (fptr = zend_hash_find_ptr(obj->method_cache, name))) {
		memset(&f, 0, sizeof(zend_internal_function));
		f.type = ZEND_INTERNAL_FUNCTION;
		f.num_args = 0;
		f.arg_info = NULL;
		f.scope = obj->ce;
		f.fn_flags = ZEND_ACC_CALL_VIA_HANDLER;
		f.function_name = zend_string_copy(name);
		f.handler = PHP_FN(com_method_handler);

		fptr = &f;

		if (obj->typeinfo) {
			/* look for byref params */
			ITypeComp *comp;
			ITypeInfo *TI = NULL;
			DESCKIND kind;
			BINDPTR bindptr;
			OLECHAR *olename;
			ULONG lhash;
			int i;

			if (SUCCEEDED(ITypeInfo_GetTypeComp(obj->typeinfo, &comp))) {
				olename = php_com_string_to_olestring(name->val, name->len, obj->code_page);
				lhash = LHashValOfNameSys(SYS_WIN32, LOCALE_SYSTEM_DEFAULT, olename);

				if (SUCCEEDED(ITypeComp_Bind(comp, olename, lhash, INVOKE_FUNC, &TI, &kind, &bindptr))) {
					switch (kind) {
						case DESCKIND_FUNCDESC:
							f.arg_info = ecalloc(bindptr.lpfuncdesc->cParams, sizeof(zend_arg_info));

							for (i = 0; i < bindptr.lpfuncdesc->cParams; i++) {
								zend_bool by_ref = (bindptr.lpfuncdesc->lprgelemdescParam[i].paramdesc.wParamFlags & PARAMFLAG_FOUT) != 0;
								f.arg_info[i].type = (zend_type) ZEND_TYPE_INIT_NONE(_ZEND_ARG_INFO_FLAGS(by_ref, 0));
							}

							f.num_args = bindptr.lpfuncdesc->cParams;

							ITypeInfo_ReleaseFuncDesc(TI, bindptr.lpfuncdesc);
							break;

							/* these should not happen, but *might* happen if the user
							 * screws up; lets avoid a leak in that case */
						case DESCKIND_VARDESC:
							ITypeInfo_ReleaseVarDesc(TI, bindptr.lpvardesc);
							break;
						case DESCKIND_TYPECOMP:
							ITypeComp_Release(bindptr.lptcomp);
							break;

						case DESCKIND_NONE:
							break;
					}
					if (TI) {
						ITypeInfo_Release(TI);
					}
				}
				ITypeComp_Release(comp);
				efree(olename);
			}
		}

		zend_set_function_arg_flags((zend_function*)&f);
		/* save this method in the cache */
		if (!obj->method_cache) {
			ALLOC_HASHTABLE(obj->method_cache);
			zend_hash_init(obj->method_cache, 2, NULL, function_dtor, 0);
		}

		zend_hash_update_mem(obj->method_cache, name, &f, sizeof(f));
	}

	if (fptr) {
		/* duplicate this into a new chunk of emalloc'd memory,
		 * since the engine will efree it */
		zend_string_addref(fptr->function_name);
		func = emalloc(sizeof(*fptr));
		memcpy(func, fptr, sizeof(*fptr));

		return func;
	}

	return NULL;
}