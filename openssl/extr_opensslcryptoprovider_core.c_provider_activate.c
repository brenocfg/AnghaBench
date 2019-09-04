#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int function_id; } ;
struct TYPE_12__ {int flag_initialized; char* path; int /*<<< orphan*/  query_operation; int /*<<< orphan*/  get_params; int /*<<< orphan*/  get_param_types; int /*<<< orphan*/  teardown; int /*<<< orphan*/ * module; int /*<<< orphan*/  name; int /*<<< orphan*/  provctx; int /*<<< orphan*/  (* init_function ) (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__ const**,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  (* OSSL_provider_init_fn ) (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__ const**,int /*<<< orphan*/ *) ;
typedef  TYPE_1__ OSSL_PROVIDER ;
typedef  TYPE_2__ OSSL_DISPATCH ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_F_PROVIDER_ACTIVATE ; 
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSO_CTRL_SET_FLAGS ; 
 int /*<<< orphan*/  DSO_FLAG_NAME_TRANSLATION_EXT_ONLY ; 
 scalar_t__ DSO_bind_func (int /*<<< orphan*/ *,char*) ; 
 char* DSO_convert_filename (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSO_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DSO_load (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* DSO_merge (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/ * DSO_new () ; 
 int /*<<< orphan*/  ERR_R_INIT_FAIL ; 
 int /*<<< orphan*/  ERR_add_error_data (int,char*,int /*<<< orphan*/ ) ; 
 char* MODULESDIR ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
#define  OSSL_FUNC_PROVIDER_GET_PARAMS 131 
#define  OSSL_FUNC_PROVIDER_GET_PARAM_TYPES 130 
#define  OSSL_FUNC_PROVIDER_QUERY_OPERATION 129 
#define  OSSL_FUNC_PROVIDER_TEARDOWN 128 
 int /*<<< orphan*/  OSSL_get_provider_get_param_types (TYPE_2__ const*) ; 
 int /*<<< orphan*/  OSSL_get_provider_get_params (TYPE_2__ const*) ; 
 int /*<<< orphan*/  OSSL_get_provider_query_operation (TYPE_2__ const*) ; 
 int /*<<< orphan*/  OSSL_get_provider_teardown (TYPE_2__ const*) ; 
 int /*<<< orphan*/  core_dispatch ; 
 char* ossl_safe_getenv (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__ const**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int provider_activate(OSSL_PROVIDER *prov)
{
    const OSSL_DISPATCH *provider_dispatch = NULL;

    if (prov->flag_initialized)
        return 1;

    /*
     * If the init function isn't set, it indicates that this provider is
     * a loadable module.
     */
    if (prov->init_function == NULL) {
        if (prov->module == NULL) {
            char *allocated_path = NULL;
            const char *module_path = NULL;
            char *merged_path = NULL;
            const char *load_dir = ossl_safe_getenv("OPENSSL_MODULES");

            if ((prov->module = DSO_new()) == NULL) {
                /* DSO_new() generates an error already */
                return 0;
            }

            if (load_dir == NULL)
                load_dir = MODULESDIR;

            DSO_ctrl(prov->module, DSO_CTRL_SET_FLAGS,
                     DSO_FLAG_NAME_TRANSLATION_EXT_ONLY, NULL);

            module_path = prov->path;
            if (module_path == NULL)
                module_path = allocated_path =
                    DSO_convert_filename(prov->module, prov->name);
            if (module_path != NULL)
                merged_path = DSO_merge(prov->module, module_path, load_dir);

            if (merged_path == NULL
                || (DSO_load(prov->module, merged_path, NULL, 0)) == NULL) {
                DSO_free(prov->module);
                prov->module = NULL;
            }

            OPENSSL_free(merged_path);
            OPENSSL_free(allocated_path);
        }

        if (prov->module != NULL)
            prov->init_function = (OSSL_provider_init_fn *)
                DSO_bind_func(prov->module, "OSSL_provider_init");
    }

    if (prov->init_function == NULL
        || !prov->init_function(prov, core_dispatch, &provider_dispatch,
                                &prov->provctx)) {
        CRYPTOerr(CRYPTO_F_PROVIDER_ACTIVATE, ERR_R_INIT_FAIL);
        ERR_add_error_data(2, "name=", prov->name);
        DSO_free(prov->module);
        prov->module = NULL;
        return 0;
    }

    for (; provider_dispatch->function_id != 0; provider_dispatch++) {
        switch (provider_dispatch->function_id) {
        case OSSL_FUNC_PROVIDER_TEARDOWN:
            prov->teardown =
                OSSL_get_provider_teardown(provider_dispatch);
            break;
        case OSSL_FUNC_PROVIDER_GET_PARAM_TYPES:
            prov->get_param_types =
                OSSL_get_provider_get_param_types(provider_dispatch);
            break;
        case OSSL_FUNC_PROVIDER_GET_PARAMS:
            prov->get_params =
                OSSL_get_provider_get_params(provider_dispatch);
            break;
        case OSSL_FUNC_PROVIDER_QUERY_OPERATION:
            prov->query_operation =
                OSSL_get_provider_query_operation(provider_dispatch);
            break;
        }
    }

    /* With this flag set, this provider has become fully "loaded". */
    prov->flag_initialized = 1;

    return 1;
}