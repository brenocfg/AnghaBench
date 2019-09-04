#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
typedef  size_t ssize_t ;
struct TYPE_27__ {char* data; int len; } ;
typedef  TYPE_4__ ngx_str_t ;
struct TYPE_28__ {int test_dir; int test_only; scalar_t__ err; int log; char* fd; int /*<<< orphan*/  failed; int /*<<< orphan*/  directio; int /*<<< orphan*/  min_uses; int /*<<< orphan*/  valid; int /*<<< orphan*/  is_dir; int /*<<< orphan*/  events; int /*<<< orphan*/  errors; } ;
typedef  TYPE_5__ ngx_open_file_info_t ;
struct TYPE_29__ {TYPE_3__* connection; int /*<<< orphan*/  pool; int /*<<< orphan*/  root_tested; } ;
typedef  TYPE_6__ ngx_http_request_t ;
struct TYPE_30__ {TYPE_2__* values; TYPE_1__* lengths; } ;
typedef  TYPE_7__ ngx_http_log_script_t ;
struct TYPE_31__ {int /*<<< orphan*/  open_file_cache; int /*<<< orphan*/  open_file_cache_min_uses; int /*<<< orphan*/  open_file_cache_valid; } ;
typedef  TYPE_8__ ngx_http_log_loc_conf_t ;
struct TYPE_32__ {int /*<<< orphan*/  open_file_cache; int /*<<< orphan*/  open_file_cache_events; int /*<<< orphan*/  open_file_cache_errors; int /*<<< orphan*/  open_file_cache_min_uses; int /*<<< orphan*/  open_file_cache_valid; } ;
typedef  TYPE_9__ ngx_http_core_loc_conf_t ;
struct TYPE_26__ {int /*<<< orphan*/  log; } ;
struct TYPE_25__ {int /*<<< orphan*/  elts; } ;
struct TYPE_24__ {int /*<<< orphan*/  elts; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ENOTDIR ; 
 int /*<<< orphan*/  NGX_LOG_CRIT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  NGX_OPEN_FILE_DIRECTIO_OFF ; 
 int /*<<< orphan*/  ngx_errno ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 void* ngx_http_get_module_loc_conf (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_log_module ; 
 int /*<<< orphan*/ * ngx_http_map_uri_to_path (TYPE_6__*,TYPE_4__*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_http_script_run (TYPE_6__*,TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_set_disable_symlinks (TYPE_6__*,TYPE_9__*,TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*,char*,...) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_5__*,int) ; 
 scalar_t__ ngx_open_cached_file (int /*<<< orphan*/ ,TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 size_t ngx_write_fd (char*,char*,size_t) ; 

__attribute__((used)) static ssize_t
ngx_http_log_script_write(ngx_http_request_t *r, ngx_http_log_script_t *script,
    u_char **name, u_char *buf, size_t len)
{
    size_t                     root;
    ssize_t                    n;
    ngx_str_t                  log, path;
    ngx_open_file_info_t       of;
    ngx_http_log_loc_conf_t   *llcf;
    ngx_http_core_loc_conf_t  *clcf;

    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);

    if (!r->root_tested) {

        /* test root directory existence */

        if (ngx_http_map_uri_to_path(r, &path, &root, 0) == NULL) {
            /* simulate successful logging */
            return len;
        }

        path.data[root] = '\0';

        ngx_memzero(&of, sizeof(ngx_open_file_info_t));

        of.valid = clcf->open_file_cache_valid;
        of.min_uses = clcf->open_file_cache_min_uses;
        of.test_dir = 1;
        of.test_only = 1;
        of.errors = clcf->open_file_cache_errors;
        of.events = clcf->open_file_cache_events;

        if (ngx_http_set_disable_symlinks(r, clcf, &path, &of) != NGX_OK) {
            /* simulate successful logging */
            return len;
        }

        if (ngx_open_cached_file(clcf->open_file_cache, &path, &of, r->pool)
            != NGX_OK)
        {
            if (of.err == 0) {
                /* simulate successful logging */
                return len;
            }

            ngx_log_error(NGX_LOG_ERR, r->connection->log, of.err,
                          "testing \"%s\" existence failed", path.data);

            /* simulate successful logging */
            return len;
        }

        if (!of.is_dir) {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, NGX_ENOTDIR,
                          "testing \"%s\" existence failed", path.data);

            /* simulate successful logging */
            return len;
        }
    }

    if (ngx_http_script_run(r, &log, script->lengths->elts, 1,
                            script->values->elts)
        == NULL)
    {
        /* simulate successful logging */
        return len;
    }

    log.data[log.len - 1] = '\0';
    *name = log.data;

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "http log \"%s\"", log.data);

    llcf = ngx_http_get_module_loc_conf(r, ngx_http_log_module);

    ngx_memzero(&of, sizeof(ngx_open_file_info_t));

    of.log = 1;
    of.valid = llcf->open_file_cache_valid;
    of.min_uses = llcf->open_file_cache_min_uses;
    of.directio = NGX_OPEN_FILE_DIRECTIO_OFF;

    if (ngx_http_set_disable_symlinks(r, clcf, &log, &of) != NGX_OK) {
        /* simulate successful logging */
        return len;
    }

    if (ngx_open_cached_file(llcf->open_file_cache, &log, &of, r->pool)
        != NGX_OK)
    {
        if (of.err == 0) {
            /* simulate successful logging */
            return len;
        }

        ngx_log_error(NGX_LOG_CRIT, r->connection->log, ngx_errno,
                      "%s \"%s\" failed", of.failed, log.data);
        /* simulate successful logging */
        return len;
    }

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "http log #%d", of.fd);

    n = ngx_write_fd(of.fd, buf, len);

    return n;
}