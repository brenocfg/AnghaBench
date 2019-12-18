#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ type; int /*<<< orphan*/  name; struct TYPE_20__* next_prop_func; struct TYPE_20__* next; } ;
typedef  TYPE_2__ function_decl_t ;
struct TYPE_21__ {scalar_t__ is_array; struct TYPE_21__* next; int /*<<< orphan*/  is_public; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ dim_decl_t ;
struct TYPE_22__ {TYPE_5__* classes; int /*<<< orphan*/  code; } ;
typedef  TYPE_4__ compile_ctx_t ;
struct TYPE_23__ {int func_cnt; unsigned int class_initialize_id; unsigned int class_terminate_id; int prop_cnt; int array_cnt; struct TYPE_23__* next; void* array_descs; TYPE_1__* props; void* funcs; void* name; } ;
typedef  TYPE_5__ class_desc_t ;
struct TYPE_24__ {TYPE_3__* props; TYPE_2__* funcs; int /*<<< orphan*/  name; } ;
typedef  TYPE_6__ class_decl_t ;
typedef  char WCHAR ;
struct TYPE_19__ {scalar_t__ is_array; int /*<<< orphan*/  is_public; void* name; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 scalar_t__ FUNC_DEFGET ; 
 scalar_t__ FUNC_SUB ; 
 int /*<<< orphan*/  S_OK ; 
 void* compiler_alloc (int /*<<< orphan*/ ,int) ; 
 void* compiler_alloc_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* compiler_alloc_zero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  create_class_funcprop (TYPE_4__*,TYPE_2__*,void*) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_array_desc (TYPE_4__*,TYPE_3__*,void*) ; 
 scalar_t__ lookup_class_funcs (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ lookup_class_name (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ lookup_const_decls (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lookup_dim_decls (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ lookup_funcs_name (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcmpiW (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT compile_class(compile_ctx_t *ctx, class_decl_t *class_decl)
{
    function_decl_t *func_decl, *func_prop_decl;
    class_desc_t *class_desc;
    dim_decl_t *prop_decl;
    unsigned i;
    HRESULT hres;

    static const WCHAR class_initializeW[] = {'c','l','a','s','s','_','i','n','i','t','i','a','l','i','z','e',0};
    static const WCHAR class_terminateW[] = {'c','l','a','s','s','_','t','e','r','m','i','n','a','t','e',0};

    if(lookup_dim_decls(ctx, class_decl->name) || lookup_funcs_name(ctx, class_decl->name)
            || lookup_const_decls(ctx, class_decl->name, FALSE) || lookup_class_name(ctx, class_decl->name)) {
        FIXME("%s: redefinition\n", debugstr_w(class_decl->name));
        return E_FAIL;
    }

    class_desc = compiler_alloc_zero(ctx->code, sizeof(*class_desc));
    if(!class_desc)
        return E_OUTOFMEMORY;

    class_desc->name = compiler_alloc_string(ctx->code, class_decl->name);
    if(!class_desc->name)
        return E_OUTOFMEMORY;

    class_desc->func_cnt = 1; /* always allocate slot for default getter */

    for(func_decl = class_decl->funcs; func_decl; func_decl = func_decl->next) {
        for(func_prop_decl = func_decl; func_prop_decl; func_prop_decl = func_prop_decl->next_prop_func) {
            if(func_prop_decl->type == FUNC_DEFGET)
                break;
        }
        if(!func_prop_decl)
            class_desc->func_cnt++;
    }

    class_desc->funcs = compiler_alloc(ctx->code, class_desc->func_cnt*sizeof(*class_desc->funcs));
    if(!class_desc->funcs)
        return E_OUTOFMEMORY;
    memset(class_desc->funcs, 0, class_desc->func_cnt*sizeof(*class_desc->funcs));

    for(func_decl = class_decl->funcs, i=1; func_decl; func_decl = func_decl->next, i++) {
        for(func_prop_decl = func_decl; func_prop_decl; func_prop_decl = func_prop_decl->next_prop_func) {
            if(func_prop_decl->type == FUNC_DEFGET) {
                i--;
                break;
            }
        }

        if(!strcmpiW(class_initializeW, func_decl->name)) {
            if(func_decl->type != FUNC_SUB) {
                FIXME("class initializer is not sub\n");
                return E_FAIL;
            }

            class_desc->class_initialize_id = i;
        }else  if(!strcmpiW(class_terminateW, func_decl->name)) {
            if(func_decl->type != FUNC_SUB) {
                FIXME("class terminator is not sub\n");
                return E_FAIL;
            }

            class_desc->class_terminate_id = i;
        }

        hres = create_class_funcprop(ctx, func_decl, class_desc->funcs + (func_prop_decl ? 0 : i));
        if(FAILED(hres))
            return hres;
    }

    for(prop_decl = class_decl->props; prop_decl; prop_decl = prop_decl->next)
        class_desc->prop_cnt++;

    class_desc->props = compiler_alloc(ctx->code, class_desc->prop_cnt*sizeof(*class_desc->props));
    if(!class_desc->props)
        return E_OUTOFMEMORY;

    for(prop_decl = class_decl->props, i=0; prop_decl; prop_decl = prop_decl->next, i++) {
        if(lookup_class_funcs(class_desc, prop_decl->name)) {
            FIXME("Property %s redefined\n", debugstr_w(prop_decl->name));
            return E_FAIL;
        }

        class_desc->props[i].name = compiler_alloc_string(ctx->code, prop_decl->name);
        if(!class_desc->props[i].name)
            return E_OUTOFMEMORY;

        class_desc->props[i].is_public = prop_decl->is_public;
        class_desc->props[i].is_array = prop_decl->is_array;

        if(prop_decl->is_array)
            class_desc->array_cnt++;
    }

    if(class_desc->array_cnt) {
        class_desc->array_descs = compiler_alloc(ctx->code, class_desc->array_cnt*sizeof(*class_desc->array_descs));
        if(!class_desc->array_descs)
            return E_OUTOFMEMORY;

        for(prop_decl = class_decl->props, i=0; prop_decl; prop_decl = prop_decl->next) {
            if(prop_decl->is_array) {
                hres = fill_array_desc(ctx, prop_decl, class_desc->array_descs + i++);
                if(FAILED(hres))
                    return hres;
            }
        }
    }

    class_desc->next = ctx->classes;
    ctx->classes = class_desc;
    return S_OK;
}