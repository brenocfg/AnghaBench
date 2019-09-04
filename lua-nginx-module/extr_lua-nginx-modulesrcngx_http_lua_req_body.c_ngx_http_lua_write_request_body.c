#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_12__ {int /*<<< orphan*/  log; int /*<<< orphan*/  fd; } ;
struct TYPE_14__ {char* warn; int persistent; int clean; int access; int /*<<< orphan*/  offset; int /*<<< orphan*/  pool; int /*<<< orphan*/  path; TYPE_11__ file; int /*<<< orphan*/  log_level; } ;
typedef  TYPE_2__ ngx_temp_file_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_15__ {scalar_t__ request_body_file_group_access; int /*<<< orphan*/  request_body_file_log_level; int /*<<< orphan*/  pool; TYPE_1__* connection; TYPE_4__* request_body; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_16__ {TYPE_2__* temp_file; } ;
typedef  TYPE_4__ ngx_http_request_body_t ;
struct TYPE_17__ {int /*<<< orphan*/  client_body_temp_path; } ;
typedef  TYPE_5__ ngx_http_core_loc_conf_t ;
typedef  int /*<<< orphan*/  ngx_chain_t ;
struct TYPE_13__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_INVALID_FILE ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_create_temp_file (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_5__* ngx_http_get_module_loc_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_write_chain_to_temp_file (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_write_request_body(ngx_http_request_t *r, ngx_chain_t *body)
{
    ssize_t                    n;
    ngx_temp_file_t           *tf;
    ngx_http_request_body_t   *rb;
    ngx_http_core_loc_conf_t  *clcf;

    rb = r->request_body;

    if (rb->temp_file == NULL) {
        tf = ngx_pcalloc(r->pool, sizeof(ngx_temp_file_t));
        if (tf == NULL) {
            return NGX_ERROR;
        }

        clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);

        tf->file.fd = NGX_INVALID_FILE;
        tf->file.log = r->connection->log;
        tf->path = clcf->client_body_temp_path;
        tf->pool = r->pool;
        tf->warn = "a client request body is buffered to a temporary file";
        tf->log_level = r->request_body_file_log_level;
        tf->persistent = 1;
        tf->clean = 1;

        if (r->request_body_file_group_access) {
            tf->access = 0660;
        }

        rb->temp_file = tf;

        if (body == NULL) {
            /* empty body with r->request_body_in_file_only */

            if (ngx_create_temp_file(&tf->file, tf->path, tf->pool,
                                     tf->persistent, tf->clean, tf->access)
                != NGX_OK)
            {
                return NGX_ERROR;
            }

            return NGX_OK;
        }
    }

    n = ngx_write_chain_to_temp_file(rb->temp_file, body);

    /* TODO: n == 0 or not complete and level event */

    if (n == NGX_ERROR) {
        return NGX_ERROR;
    }

    rb->temp_file->offset += n;

    return NGX_OK;
}