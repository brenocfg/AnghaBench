#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  data; scalar_t__ len; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_24__ {int test_only; scalar_t__ err; int /*<<< orphan*/  is_exec; int /*<<< orphan*/  is_link; int /*<<< orphan*/  is_dir; int /*<<< orphan*/  is_file; int /*<<< orphan*/  failed; int /*<<< orphan*/  events; int /*<<< orphan*/  errors; int /*<<< orphan*/  min_uses; int /*<<< orphan*/  valid; int /*<<< orphan*/  directio; int /*<<< orphan*/  read_ahead; } ;
typedef  TYPE_3__ ngx_open_file_info_t ;
struct TYPE_25__ {int /*<<< orphan*/  data; scalar_t__ len; } ;
typedef  TYPE_4__ ngx_http_variable_value_t ;
struct TYPE_26__ {int op; } ;
typedef  TYPE_5__ ngx_http_script_file_code_t ;
struct TYPE_27__ {void* status; void* ip; TYPE_7__* request; TYPE_4__* sp; } ;
typedef  TYPE_6__ ngx_http_script_engine_t ;
struct TYPE_28__ {TYPE_1__* connection; int /*<<< orphan*/  pool; } ;
typedef  TYPE_7__ ngx_http_request_t ;
struct TYPE_29__ {int /*<<< orphan*/  open_file_cache; int /*<<< orphan*/  open_file_cache_events; int /*<<< orphan*/  open_file_cache_errors; int /*<<< orphan*/  open_file_cache_min_uses; int /*<<< orphan*/  open_file_cache_valid; int /*<<< orphan*/  directio; int /*<<< orphan*/  read_ahead; } ;
typedef  TYPE_8__ ngx_http_core_loc_conf_t ;
struct TYPE_22__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_ENAMETOOLONG ; 
 scalar_t__ NGX_ENOENT ; 
 scalar_t__ NGX_ENOTDIR ; 
 void* NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_CRIT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_8__* ngx_http_get_module_loc_conf (TYPE_7__*,int /*<<< orphan*/ ) ; 
 void* ngx_http_script_exit ; 
#define  ngx_http_script_file_dir 135 
#define  ngx_http_script_file_exec 134 
#define  ngx_http_script_file_exists 133 
#define  ngx_http_script_file_not_dir 132 
#define  ngx_http_script_file_not_exec 131 
#define  ngx_http_script_file_not_exists 130 
#define  ngx_http_script_file_not_plain 129 
#define  ngx_http_script_file_plain 128 
 scalar_t__ ngx_http_set_disable_symlinks (TYPE_7__*,TYPE_8__*,TYPE_2__*,TYPE_3__*) ; 
 TYPE_4__ ngx_http_variable_null_value ; 
 TYPE_4__ ngx_http_variable_true_value ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_3__*,int) ; 
 scalar_t__ ngx_open_cached_file (int /*<<< orphan*/ ,TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ) ; 

void
ngx_http_script_file_code(ngx_http_script_engine_t *e)
{
    ngx_str_t                     path;
    ngx_http_request_t           *r;
    ngx_open_file_info_t          of;
    ngx_http_core_loc_conf_t     *clcf;
    ngx_http_variable_value_t    *value;
    ngx_http_script_file_code_t  *code;

    value = e->sp - 1;

    code = (ngx_http_script_file_code_t *) e->ip;
    e->ip += sizeof(ngx_http_script_file_code_t);

    path.len = value->len - 1;
    path.data = value->data;

    r = e->request;

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "http script file op %p \"%V\"", (void *) code->op, &path);

    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);

    ngx_memzero(&of, sizeof(ngx_open_file_info_t));

    of.read_ahead = clcf->read_ahead;
    of.directio = clcf->directio;
    of.valid = clcf->open_file_cache_valid;
    of.min_uses = clcf->open_file_cache_min_uses;
    of.test_only = 1;
    of.errors = clcf->open_file_cache_errors;
    of.events = clcf->open_file_cache_events;

    if (ngx_http_set_disable_symlinks(r, clcf, &path, &of) != NGX_OK) {
        e->ip = ngx_http_script_exit;
        e->status = NGX_HTTP_INTERNAL_SERVER_ERROR;
        return;
    }

    if (ngx_open_cached_file(clcf->open_file_cache, &path, &of, r->pool)
        != NGX_OK)
    {
        if (of.err == 0) {
            e->ip = ngx_http_script_exit;
            e->status = NGX_HTTP_INTERNAL_SERVER_ERROR;
            return;
        }

        if (of.err != NGX_ENOENT
            && of.err != NGX_ENOTDIR
            && of.err != NGX_ENAMETOOLONG)
        {
            ngx_log_error(NGX_LOG_CRIT, r->connection->log, of.err,
                          "%s \"%s\" failed", of.failed, value->data);
        }

        switch (code->op) {

        case ngx_http_script_file_plain:
        case ngx_http_script_file_dir:
        case ngx_http_script_file_exists:
        case ngx_http_script_file_exec:
             goto false_value;

        case ngx_http_script_file_not_plain:
        case ngx_http_script_file_not_dir:
        case ngx_http_script_file_not_exists:
        case ngx_http_script_file_not_exec:
             goto true_value;
        }

        goto false_value;
    }

    switch (code->op) {
    case ngx_http_script_file_plain:
        if (of.is_file) {
             goto true_value;
        }
        goto false_value;

    case ngx_http_script_file_not_plain:
        if (of.is_file) {
            goto false_value;
        }
        goto true_value;

    case ngx_http_script_file_dir:
        if (of.is_dir) {
             goto true_value;
        }
        goto false_value;

    case ngx_http_script_file_not_dir:
        if (of.is_dir) {
            goto false_value;
        }
        goto true_value;

    case ngx_http_script_file_exists:
        if (of.is_file || of.is_dir || of.is_link) {
             goto true_value;
        }
        goto false_value;

    case ngx_http_script_file_not_exists:
        if (of.is_file || of.is_dir || of.is_link) {
            goto false_value;
        }
        goto true_value;

    case ngx_http_script_file_exec:
        if (of.is_exec) {
             goto true_value;
        }
        goto false_value;

    case ngx_http_script_file_not_exec:
        if (of.is_exec) {
            goto false_value;
        }
        goto true_value;
    }

false_value:

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "http script file op false");

    *value = ngx_http_variable_null_value;
    return;

true_value:

    *value = ngx_http_variable_true_value;
    return;
}