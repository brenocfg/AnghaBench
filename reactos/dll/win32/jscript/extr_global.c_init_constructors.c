#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  vbarray_constr; int /*<<< orphan*/  global; int /*<<< orphan*/  string_constr; int /*<<< orphan*/  regexp_constr; int /*<<< orphan*/  number_constr; int /*<<< orphan*/  uri_error_constr; int /*<<< orphan*/  type_error_constr; int /*<<< orphan*/  syntax_error_constr; int /*<<< orphan*/  regexp_error_constr; int /*<<< orphan*/  reference_error_constr; int /*<<< orphan*/  range_error_constr; int /*<<< orphan*/  eval_error_constr; int /*<<< orphan*/  error_constr; int /*<<< orphan*/  enumerator_constr; int /*<<< orphan*/  date_constr; int /*<<< orphan*/  bool_constr; int /*<<< orphan*/  array_constr; int /*<<< orphan*/  object_constr; int /*<<< orphan*/  function_constr; } ;
typedef  TYPE_1__ script_ctx_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ArrayW ; 
 int /*<<< orphan*/  BooleanW ; 
 int /*<<< orphan*/  DateW ; 
 int /*<<< orphan*/  EnumeratorW ; 
 int /*<<< orphan*/  ErrorW ; 
 int /*<<< orphan*/  EvalErrorW ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionW ; 
 int /*<<< orphan*/  NumberW ; 
 int /*<<< orphan*/  ObjectW ; 
 int /*<<< orphan*/  PROPF_WRITABLE ; 
 int /*<<< orphan*/  RangeErrorW ; 
 int /*<<< orphan*/  ReferenceErrorW ; 
 int /*<<< orphan*/  RegExpErrorW ; 
 int /*<<< orphan*/  RegExpW ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  StringW ; 
 int /*<<< orphan*/  SyntaxErrorW ; 
 int /*<<< orphan*/  TypeErrorW ; 
 int /*<<< orphan*/  URIErrorW ; 
 int /*<<< orphan*/  VBArrayW ; 
 int /*<<< orphan*/  create_array_constr (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_bool_constr (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_date_constr (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_enumerator_constr (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_number_constr (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_object_constr (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_regexp_constr (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_string_constr (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_vbarray_constr (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_error_constr (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_function_constr (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsdisp_define_data_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_obj (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT init_constructors(script_ctx_t *ctx, jsdisp_t *object_prototype)
{
    HRESULT hres;

    hres = init_function_constr(ctx, object_prototype);
    if(FAILED(hres))
        return hres;

    hres = jsdisp_define_data_property(ctx->global, FunctionW, PROPF_WRITABLE,
                                       jsval_obj(ctx->function_constr));
    if(FAILED(hres))
        return hres;

    hres = create_object_constr(ctx, object_prototype, &ctx->object_constr);
    if(FAILED(hres))
        return hres;

    hres = jsdisp_define_data_property(ctx->global, ObjectW, PROPF_WRITABLE,
                                       jsval_obj(ctx->object_constr));
    if(FAILED(hres))
        return hres;

    hres = create_array_constr(ctx, object_prototype, &ctx->array_constr);
    if(FAILED(hres))
        return hres;

    hres = jsdisp_define_data_property(ctx->global, ArrayW, PROPF_WRITABLE,
                                       jsval_obj(ctx->array_constr));
    if(FAILED(hres))
        return hres;

    hres = create_bool_constr(ctx, object_prototype, &ctx->bool_constr);
    if(FAILED(hres))
        return hres;

    hres = jsdisp_define_data_property(ctx->global, BooleanW, PROPF_WRITABLE,
                                       jsval_obj(ctx->bool_constr));
    if(FAILED(hres))
        return hres;

    hres = create_date_constr(ctx, object_prototype, &ctx->date_constr);
    if(FAILED(hres))
        return hres;

    hres = jsdisp_define_data_property(ctx->global, DateW, PROPF_WRITABLE,
                                       jsval_obj(ctx->date_constr));
    if(FAILED(hres))
        return hres;

    hres = create_enumerator_constr(ctx, object_prototype, &ctx->enumerator_constr);
    if(FAILED(hres))
        return hres;

    hres = jsdisp_define_data_property(ctx->global, EnumeratorW, PROPF_WRITABLE,
                                       jsval_obj(ctx->enumerator_constr));
    if(FAILED(hres))
        return hres;

    hres = init_error_constr(ctx, object_prototype);
    if(FAILED(hres))
        return hres;

    hres = jsdisp_define_data_property(ctx->global, ErrorW, PROPF_WRITABLE,
                                       jsval_obj(ctx->error_constr));
    if(FAILED(hres))
        return hres;

    hres = jsdisp_define_data_property(ctx->global, EvalErrorW, PROPF_WRITABLE,
                                       jsval_obj(ctx->eval_error_constr));
    if(FAILED(hres))
        return hres;

    hres = jsdisp_define_data_property(ctx->global, RangeErrorW, PROPF_WRITABLE,
                                       jsval_obj(ctx->range_error_constr));
    if(FAILED(hres))
        return hres;

    hres = jsdisp_define_data_property(ctx->global, ReferenceErrorW, PROPF_WRITABLE,
                                       jsval_obj(ctx->reference_error_constr));
    if(FAILED(hres))
        return hres;

    hres = jsdisp_define_data_property(ctx->global, RegExpErrorW, PROPF_WRITABLE,
                                       jsval_obj(ctx->regexp_error_constr));
    if(FAILED(hres))
        return hres;

    hres = jsdisp_define_data_property(ctx->global, SyntaxErrorW, PROPF_WRITABLE,
                                       jsval_obj(ctx->syntax_error_constr));
    if(FAILED(hres))
        return hres;

    hres = jsdisp_define_data_property(ctx->global, TypeErrorW, PROPF_WRITABLE,
                                       jsval_obj(ctx->type_error_constr));
    if(FAILED(hres))
        return hres;

    hres = jsdisp_define_data_property(ctx->global, URIErrorW, PROPF_WRITABLE,
                                       jsval_obj(ctx->uri_error_constr));
    if(FAILED(hres))
        return hres;

    hres = create_number_constr(ctx, object_prototype, &ctx->number_constr);
    if(FAILED(hres))
        return hres;

    hres = jsdisp_define_data_property(ctx->global, NumberW, PROPF_WRITABLE,
                                       jsval_obj(ctx->number_constr));
    if(FAILED(hres))
        return hres;

    hres = create_regexp_constr(ctx, object_prototype, &ctx->regexp_constr);
    if(FAILED(hres))
        return hres;

    hres = jsdisp_define_data_property(ctx->global, RegExpW, PROPF_WRITABLE,
                                       jsval_obj(ctx->regexp_constr));
    if(FAILED(hres))
        return hres;

    hres = create_string_constr(ctx, object_prototype, &ctx->string_constr);
    if(FAILED(hres))
        return hres;

    hres = jsdisp_define_data_property(ctx->global, StringW, PROPF_WRITABLE,
                                       jsval_obj(ctx->string_constr));
    if(FAILED(hres))
        return hres;

    hres = create_vbarray_constr(ctx, object_prototype, &ctx->vbarray_constr);
    if(FAILED(hres))
        return hres;

    hres = jsdisp_define_data_property(ctx->global, VBArrayW, PROPF_WRITABLE,
                                       jsval_obj(ctx->vbarray_constr));
    if(FAILED(hres))
        return hres;

    return S_OK;
}