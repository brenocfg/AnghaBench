#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
typedef  scalar_t__ ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_variable_value_t ;
struct TYPE_16__ {scalar_t__ content_length_n; } ;
struct TYPE_19__ {int method; int /*<<< orphan*/ * variables; int /*<<< orphan*/  pool; TYPE_2__* connection; int /*<<< orphan*/  method_name; TYPE_5__* request_body; TYPE_1__ headers_in; int /*<<< orphan*/  header_in; struct TYPE_19__* parent; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_20__ {scalar_t__ temp_file; scalar_t__ buf; } ;
typedef  TYPE_5__ ngx_http_request_body_t ;
struct TYPE_18__ {int nelts; } ;
struct TYPE_21__ {TYPE_3__ variables; } ;
typedef  TYPE_6__ ngx_http_core_main_conf_t ;
typedef  int /*<<< orphan*/  ngx_array_t ;
struct TYPE_17__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
#define  NGX_HTTP_COPY 142 
#define  NGX_HTTP_DELETE 141 
#define  NGX_HTTP_GET 140 
#define  NGX_HTTP_HEAD 139 
#define  NGX_HTTP_LOCK 138 
 unsigned int NGX_HTTP_LUA_COPY_ALL_VARS ; 
 unsigned int NGX_HTTP_LUA_SHARE_ALL_VARS ; 
#define  NGX_HTTP_MKCOL 137 
#define  NGX_HTTP_MOVE 136 
#define  NGX_HTTP_OPTIONS 135 
#define  NGX_HTTP_PATCH 134 
#define  NGX_HTTP_POST 133 
#define  NGX_HTTP_PROPFIND 132 
#define  NGX_HTTP_PROPPATCH 131 
#define  NGX_HTTP_PUT 130 
#define  NGX_HTTP_TRACE 129 
#define  NGX_HTTP_UNLOCK 128 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_buf_size (scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_6__* ngx_http_get_module_main_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_lua_copy_in_file_request_body (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_lua_copy_method ; 
 scalar_t__ ngx_http_lua_copy_request_headers (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_lua_delete_method ; 
 int /*<<< orphan*/  ngx_http_lua_get_method ; 
 int /*<<< orphan*/  ngx_http_lua_head_method ; 
 int /*<<< orphan*/  ngx_http_lua_lock_method ; 
 int /*<<< orphan*/  ngx_http_lua_mkcol_method ; 
 int /*<<< orphan*/  ngx_http_lua_move_method ; 
 int /*<<< orphan*/  ngx_http_lua_options_method ; 
 int /*<<< orphan*/  ngx_http_lua_patch_method ; 
 int /*<<< orphan*/  ngx_http_lua_post_method ; 
 int /*<<< orphan*/  ngx_http_lua_propfind_method ; 
 int /*<<< orphan*/  ngx_http_lua_proppatch_method ; 
 int /*<<< orphan*/  ngx_http_lua_put_method ; 
 scalar_t__ ngx_http_lua_set_content_length_header (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_lua_subrequest_add_extra_vars (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_trace_method ; 
 int /*<<< orphan*/  ngx_http_lua_unlock_method ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * ngx_palloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * ngx_pcalloc (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_adjust_subrequest(ngx_http_request_t *sr, ngx_uint_t method,
    int always_forward_body, ngx_http_request_body_t *body,
    unsigned vars_action, ngx_array_t *extra_vars)
{
    ngx_http_request_t          *r;
    ngx_int_t                    rc;
    ngx_http_core_main_conf_t   *cmcf;
    size_t                       size;

    r = sr->parent;

    sr->header_in = r->header_in;

    if (body) {
        sr->request_body = body;

        rc = ngx_http_lua_set_content_length_header(sr,
                                                    body->buf
                                                    ? ngx_buf_size(body->buf)
                                                    : 0);

        if (rc != NGX_OK) {
            return NGX_ERROR;
        }

    } else if (!always_forward_body
               && method != NGX_HTTP_PUT
               && method != NGX_HTTP_POST
               && r->headers_in.content_length_n > 0)
    {
        rc = ngx_http_lua_set_content_length_header(sr, 0);
        if (rc != NGX_OK) {
            return NGX_ERROR;
        }

#if 1
        sr->request_body = NULL;
#endif

    } else {
        if (ngx_http_lua_copy_request_headers(sr, r) != NGX_OK) {
            return NGX_ERROR;
        }

        if (sr->request_body) {

            /* deep-copy the request body */

            if (sr->request_body->temp_file) {
                if (ngx_http_lua_copy_in_file_request_body(sr) != NGX_OK) {
                    return NGX_ERROR;
                }
            }
        }
    }

    sr->method = method;

    switch (method) {
        case NGX_HTTP_GET:
            sr->method_name = ngx_http_lua_get_method;
            break;

        case NGX_HTTP_POST:
            sr->method_name = ngx_http_lua_post_method;
            break;

        case NGX_HTTP_PUT:
            sr->method_name = ngx_http_lua_put_method;
            break;

        case NGX_HTTP_HEAD:
            sr->method_name = ngx_http_lua_head_method;
            break;

        case NGX_HTTP_DELETE:
            sr->method_name = ngx_http_lua_delete_method;
            break;

        case NGX_HTTP_OPTIONS:
            sr->method_name = ngx_http_lua_options_method;
            break;

        case NGX_HTTP_MKCOL:
            sr->method_name = ngx_http_lua_mkcol_method;
            break;

        case NGX_HTTP_COPY:
            sr->method_name = ngx_http_lua_copy_method;
            break;

        case NGX_HTTP_MOVE:
            sr->method_name = ngx_http_lua_move_method;
            break;

        case NGX_HTTP_PROPFIND:
            sr->method_name = ngx_http_lua_propfind_method;
            break;

        case NGX_HTTP_PROPPATCH:
            sr->method_name = ngx_http_lua_proppatch_method;
            break;

        case NGX_HTTP_LOCK:
            sr->method_name = ngx_http_lua_lock_method;
            break;

        case NGX_HTTP_UNLOCK:
            sr->method_name = ngx_http_lua_unlock_method;
            break;

        case NGX_HTTP_PATCH:
            sr->method_name = ngx_http_lua_patch_method;
            break;

        case NGX_HTTP_TRACE:
            sr->method_name = ngx_http_lua_trace_method;
            break;

        default:
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                          "unsupported HTTP method: %u", (unsigned) method);

            return NGX_ERROR;
    }

    if (!(vars_action & NGX_HTTP_LUA_SHARE_ALL_VARS)) {
        /* we do not inherit the parent request's variables */
        cmcf = ngx_http_get_module_main_conf(sr, ngx_http_core_module);

        size = cmcf->variables.nelts * sizeof(ngx_http_variable_value_t);

        if (vars_action & NGX_HTTP_LUA_COPY_ALL_VARS) {

            sr->variables = ngx_palloc(sr->pool, size);
            if (sr->variables == NULL) {
                return NGX_ERROR;
            }

            ngx_memcpy(sr->variables, r->variables, size);

        } else {

            /* we do not inherit the parent request's variables */

            sr->variables = ngx_pcalloc(sr->pool, size);
            if (sr->variables == NULL) {
                return NGX_ERROR;
            }
        }
    }

    return ngx_http_lua_subrequest_add_extra_vars(sr, extra_vars);
}