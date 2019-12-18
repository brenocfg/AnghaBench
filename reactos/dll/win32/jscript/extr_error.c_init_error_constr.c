#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * uri_error_constr; int /*<<< orphan*/ * type_error_constr; int /*<<< orphan*/ * syntax_error_constr; int /*<<< orphan*/ * regexp_error_constr; int /*<<< orphan*/ * reference_error_constr; int /*<<< orphan*/ * range_error_constr; int /*<<< orphan*/ * eval_error_constr; int /*<<< orphan*/ * error_constr; } ;
typedef  TYPE_1__ script_ctx_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  builtin_invoke_t ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
#define  ErrorConstr_value 135 
#define  EvalErrorConstr_value 134 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int PROPF_CONFIGURABLE ; 
 int PROPF_CONSTR ; 
 int PROPF_WRITABLE ; 
#define  RangeErrorConstr_value 133 
#define  ReferenceErrorConstr_value 132 
#define  RegExpErrorConstr_value 131 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
#define  SyntaxErrorConstr_value 130 
#define  TypeErrorConstr_value 129 
#define  URIErrorConstr_value 128 
 int /*<<< orphan*/  alloc_error (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  create_builtin_constructor (TYPE_1__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  jsdisp_define_data_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jsstr_alloc (char const*) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nameW ; 

HRESULT init_error_constr(script_ctx_t *ctx, jsdisp_t *object_prototype)
{
    static const WCHAR ErrorW[] = {'E','r','r','o','r',0};
    static const WCHAR EvalErrorW[] = {'E','v','a','l','E','r','r','o','r',0};
    static const WCHAR RangeErrorW[] = {'R','a','n','g','e','E','r','r','o','r',0};
    static const WCHAR ReferenceErrorW[] = {'R','e','f','e','r','e','n','c','e','E','r','r','o','r',0};
    static const WCHAR RegExpErrorW[] = {'R','e','g','E','x','p','E','r','r','o','r',0};
    static const WCHAR SyntaxErrorW[] = {'S','y','n','t','a','x','E','r','r','o','r',0};
    static const WCHAR TypeErrorW[] = {'T','y','p','e','E','r','r','o','r',0};
    static const WCHAR URIErrorW[] = {'U','R','I','E','r','r','o','r',0};
    static const WCHAR *names[] = {ErrorW, EvalErrorW, RangeErrorW,
        ReferenceErrorW, RegExpErrorW, SyntaxErrorW, TypeErrorW, URIErrorW};
    jsdisp_t **constr_addr[] = {&ctx->error_constr, &ctx->eval_error_constr,
        &ctx->range_error_constr, &ctx->reference_error_constr, &ctx->regexp_error_constr,
        &ctx->syntax_error_constr, &ctx->type_error_constr,
        &ctx->uri_error_constr};
    static builtin_invoke_t constr_val[] = {ErrorConstr_value, EvalErrorConstr_value,
        RangeErrorConstr_value, ReferenceErrorConstr_value, RegExpErrorConstr_value,
        SyntaxErrorConstr_value, TypeErrorConstr_value, URIErrorConstr_value};

    jsdisp_t *err;
    unsigned int i;
    jsstr_t *str;
    HRESULT hres;

    for(i=0; i < ARRAY_SIZE(names); i++) {
        hres = alloc_error(ctx, i==0 ? object_prototype : NULL, NULL, &err);
        if(FAILED(hres))
            return hres;

        str = jsstr_alloc(names[i]);
        if(!str) {
            jsdisp_release(err);
            return E_OUTOFMEMORY;
        }

        hres = jsdisp_define_data_property(err, nameW, PROPF_WRITABLE | PROPF_CONFIGURABLE,
                                           jsval_string(str));
        jsstr_release(str);
        if(SUCCEEDED(hres))
            hres = create_builtin_constructor(ctx, constr_val[i], names[i], NULL,
                    PROPF_CONSTR|1, err, constr_addr[i]);

        jsdisp_release(err);
        if(FAILED(hres))
            return hres;
    }

    return S_OK;
}