#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_39__   TYPE_9__ ;
typedef  struct TYPE_38__   TYPE_8__ ;
typedef  struct TYPE_37__   TYPE_7__ ;
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_24__ ;
typedef  struct TYPE_30__   TYPE_21__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_13__ ;
typedef  struct TYPE_27__   TYPE_12__ ;
typedef  struct TYPE_26__   TYPE_11__ ;
typedef  struct TYPE_25__   TYPE_10__ ;

/* Type definitions */
typedef  int time_t ;
struct TYPE_30__ {int /*<<< orphan*/  data; } ;
struct TYPE_31__ {scalar_t__ fd; TYPE_21__ name; int /*<<< orphan*/  log; } ;
struct TYPE_39__ {int persistent; TYPE_24__ file; int /*<<< orphan*/  access; int /*<<< orphan*/  clean; int /*<<< orphan*/  pool; int /*<<< orphan*/  path; } ;
typedef  TYPE_9__ ngx_temp_file_t ;
struct TYPE_25__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
typedef  TYPE_10__ ngx_str_t ;
struct TYPE_34__ {TYPE_3__* last_modified; } ;
struct TYPE_26__ {scalar_t__ store; TYPE_7__* conf; TYPE_4__ headers_in; TYPE_1__* pipe; } ;
typedef  TYPE_11__ ngx_http_upstream_t ;
struct TYPE_27__ {TYPE_8__* connection; int /*<<< orphan*/  pool; } ;
typedef  TYPE_12__ ngx_http_request_t ;
struct TYPE_28__ {int time; int create_path; int delete_file; scalar_t__ fd; int /*<<< orphan*/  log; int /*<<< orphan*/  path_access; int /*<<< orphan*/  access; } ;
typedef  TYPE_13__ ngx_ext_rename_file_t ;
struct TYPE_38__ {int /*<<< orphan*/  log; } ;
struct TYPE_37__ {TYPE_6__* store_values; TYPE_5__* store_lengths; int /*<<< orphan*/  store_access; int /*<<< orphan*/  temp_path; } ;
struct TYPE_36__ {int /*<<< orphan*/  elts; } ;
struct TYPE_35__ {int /*<<< orphan*/  elts; } ;
struct TYPE_32__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_33__ {TYPE_2__ value; } ;
struct TYPE_29__ {TYPE_9__* temp_file; } ;

/* Variables and functions */
 int NGX_ERROR ; 
 scalar_t__ NGX_INVALID_FILE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_create_temp_file (TYPE_24__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_ext_rename_file (TYPE_21__*,TYPE_10__*,TYPE_13__*) ; 
 int /*<<< orphan*/ * ngx_http_map_uri_to_path (TYPE_12__*,TYPE_10__*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_http_script_run (TYPE_12__*,TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ngx_parse_http_time (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_9__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ngx_http_upstream_store(ngx_http_request_t *r, ngx_http_upstream_t *u)
{
    size_t                  root;
    time_t                  lm;
    ngx_str_t               path;
    ngx_temp_file_t        *tf;
    ngx_ext_rename_file_t   ext;

    tf = u->pipe->temp_file;

    if (tf->file.fd == NGX_INVALID_FILE) {

        /* create file for empty 200 response */

        tf = ngx_pcalloc(r->pool, sizeof(ngx_temp_file_t));
        if (tf == NULL) {
            return;
        }

        tf->file.fd = NGX_INVALID_FILE;
        tf->file.log = r->connection->log;
        tf->path = u->conf->temp_path;
        tf->pool = r->pool;
        tf->persistent = 1;

        if (ngx_create_temp_file(&tf->file, tf->path, tf->pool,
                                 tf->persistent, tf->clean, tf->access)
            != NGX_OK)
        {
            return;
        }

        u->pipe->temp_file = tf;
    }

    ext.access = u->conf->store_access;
    ext.path_access = u->conf->store_access;
    ext.time = -1;
    ext.create_path = 1;
    ext.delete_file = 1;
    ext.log = r->connection->log;

    if (u->headers_in.last_modified) {

        lm = ngx_parse_http_time(u->headers_in.last_modified->value.data,
                                 u->headers_in.last_modified->value.len);

        if (lm != NGX_ERROR) {
            ext.time = lm;
            ext.fd = tf->file.fd;
        }
    }

    if (u->conf->store_lengths == NULL) {

        if (ngx_http_map_uri_to_path(r, &path, &root, 0) == NULL) {
            return;
        }

    } else {
        if (ngx_http_script_run(r, &path, u->conf->store_lengths->elts, 0,
                                u->conf->store_values->elts)
            == NULL)
        {
            return;
        }
    }

    path.len--;

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "upstream stores \"%s\" to \"%s\"",
                   tf->file.name.data, path.data);

    (void) ngx_ext_rename_file(&tf->file.name, &path, &ext);

    u->store = 0;
}