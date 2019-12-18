#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  char ngx_uint_t ;
struct TYPE_15__ {scalar_t__ data; scalar_t__ len; } ;
typedef  TYPE_3__ ngx_str_t ;
struct TYPE_16__ {char nelts; TYPE_5__* elts; struct TYPE_16__* next; } ;
typedef  TYPE_4__ ngx_list_part_t ;
struct TYPE_14__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_17__ {char key; TYPE_3__ value; TYPE_2__ name; } ;
typedef  TYPE_5__ ngx_http_ssi_var_t ;
struct TYPE_18__ {char ncaptures; scalar_t__ captures_data; scalar_t__* captures; TYPE_1__* variables; } ;
typedef  TYPE_6__ ngx_http_ssi_ctx_t ;
struct TYPE_19__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  main; } ;
typedef  TYPE_7__ ngx_http_request_t ;
struct TYPE_13__ {TYPE_4__ part; } ;

/* Variables and functions */
 TYPE_6__* ngx_http_get_module_ctx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_ssi_filter_module ; 
 TYPE_3__* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_strncmp (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static ngx_str_t *
ngx_http_ssi_get_variable(ngx_http_request_t *r, ngx_str_t *name,
    ngx_uint_t key)
{
    ngx_uint_t           i;
    ngx_list_part_t     *part;
    ngx_http_ssi_var_t  *var;
    ngx_http_ssi_ctx_t  *ctx;

    ctx = ngx_http_get_module_ctx(r->main, ngx_http_ssi_filter_module);

#if (NGX_PCRE)
    {
    ngx_str_t  *value;

    if (key >= '0' && key <= '9') {
        i = key - '0';

        if (i < ctx->ncaptures) {
            value = ngx_palloc(r->pool, sizeof(ngx_str_t));
            if (value == NULL) {
                return NULL;
            }

            i *= 2;

            value->data = ctx->captures_data + ctx->captures[i];
            value->len = ctx->captures[i + 1] - ctx->captures[i];

            return value;
        }
    }
    }
#endif

    if (ctx->variables == NULL) {
        return NULL;
    }

    part = &ctx->variables->part;
    var = part->elts;

    for (i = 0; /* void */ ; i++) {

        if (i >= part->nelts) {
            if (part->next == NULL) {
                break;
            }

            part = part->next;
            var = part->elts;
            i = 0;
        }

        if (name->len != var[i].name.len) {
            continue;
        }

        if (key != var[i].key) {
            continue;
        }

        if (ngx_strncmp(name->data, var[i].name.data, name->len) == 0) {
            return &var[i].value;
        }
    }

    return NULL;
}