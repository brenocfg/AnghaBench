#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
struct TYPE_6__ {char* ptr; int /*<<< orphan*/  end; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ json_parse_ctx_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  create_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  create_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 int /*<<< orphan*/  falseW ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_keyword (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iswdigit (char) ; 
 int /*<<< orphan*/  jsdisp_propput_idx (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_propput_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jsstr_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_bool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_null () ; 
 int /*<<< orphan*/  jsval_number (int) ; 
 int /*<<< orphan*/  jsval_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nullW ; 
 int /*<<< orphan*/  parse_decimal (char**,int /*<<< orphan*/ ,double*) ; 
 int /*<<< orphan*/  parse_json_string (TYPE_1__*,int /*<<< orphan*/ **) ; 
 char skip_spaces (TYPE_1__*) ; 
 int /*<<< orphan*/  trueW ; 

__attribute__((used)) static HRESULT parse_json_value(json_parse_ctx_t *ctx, jsval_t *r)
{
    HRESULT hres;

    switch(skip_spaces(ctx)) {

    /* JSONNullLiteral */
    case 'n':
        if(!is_keyword(ctx, nullW))
            break;
        *r = jsval_null();
        return S_OK;

    /* JSONBooleanLiteral */
    case 't':
        if(!is_keyword(ctx, trueW))
            break;
        *r = jsval_bool(TRUE);
        return S_OK;
    case 'f':
        if(!is_keyword(ctx, falseW))
            break;
        *r = jsval_bool(FALSE);
        return S_OK;

    /* JSONObject */
    case '{': {
        WCHAR *prop_name;
        jsdisp_t *obj;
        jsval_t val;

        hres = create_object(ctx->ctx, NULL, &obj);
        if(FAILED(hres))
            return hres;

        ctx->ptr++;
        if(skip_spaces(ctx) == '}') {
            ctx->ptr++;
            *r = jsval_obj(obj);
            return S_OK;
        }

        while(1) {
            if(*ctx->ptr != '"')
                break;
            hres = parse_json_string(ctx, &prop_name);
            if(FAILED(hres))
                break;

            if(skip_spaces(ctx) != ':') {
                FIXME("missing ':'\n");
                heap_free(prop_name);
                break;
            }

            ctx->ptr++;
            hres = parse_json_value(ctx, &val);
            if(SUCCEEDED(hres)) {
                hres = jsdisp_propput_name(obj, prop_name, val);
                jsval_release(val);
            }
            heap_free(prop_name);
            if(FAILED(hres))
                break;

            if(skip_spaces(ctx) == '}') {
                ctx->ptr++;
                *r = jsval_obj(obj);
                return S_OK;
            }

            if(*ctx->ptr++ != ',') {
                FIXME("expected ','\n");
                break;
            }
            skip_spaces(ctx);
        }

        jsdisp_release(obj);
        break;
    }

    /* JSONString */
    case '"': {
        WCHAR *string;
        jsstr_t *str;

        hres = parse_json_string(ctx, &string);
        if(FAILED(hres))
            return hres;

        /* FIXME: avoid reallocation */
        str = jsstr_alloc(string);
        heap_free(string);
        if(!str)
            return E_OUTOFMEMORY;

        *r = jsval_string(str);
        return S_OK;
    }

    /* JSONArray */
    case '[': {
        jsdisp_t *array;
        unsigned i = 0;
        jsval_t val;

        hres = create_array(ctx->ctx, 0, &array);
        if(FAILED(hres))
            return hres;

        ctx->ptr++;
        if(skip_spaces(ctx) == ']') {
            ctx->ptr++;
            *r = jsval_obj(array);
            return S_OK;
        }

        while(1) {
            hres = parse_json_value(ctx, &val);
            if(FAILED(hres))
                break;

            hres = jsdisp_propput_idx(array, i, val);
            jsval_release(val);
            if(FAILED(hres))
                break;

            if(skip_spaces(ctx) == ']') {
                ctx->ptr++;
                *r = jsval_obj(array);
                return S_OK;
            }

            if(*ctx->ptr != ',') {
                FIXME("expected ','\n");
                break;
            }

            ctx->ptr++;
            i++;
        }

        jsdisp_release(array);
        break;
    }

    /* JSONNumber */
    default: {
        int sign = 1;
        double n;

        if(*ctx->ptr == '-') {
            sign = -1;
            ctx->ptr++;
            skip_spaces(ctx);
        }

        if(*ctx->ptr == '0' && ctx->ptr + 1 < ctx->end && iswdigit(ctx->ptr[1]))
            break;

        hres = parse_decimal(&ctx->ptr, ctx->end, &n);
        if(FAILED(hres))
            break;

        *r = jsval_number(sign*n);
        return S_OK;
    }
    }

    FIXME("Syntax error at %s\n", debugstr_w(ctx->ptr));
    return E_FAIL;
}