#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
struct TYPE_19__ {int len; char* data; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_20__ {int test_dir; int test_only; scalar_t__ err; scalar_t__ is_dir; int /*<<< orphan*/  failed; int /*<<< orphan*/  errors; int /*<<< orphan*/  valid; } ;
typedef  TYPE_3__ ngx_open_file_info_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_21__ {TYPE_1__* connection; int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_22__ {int /*<<< orphan*/  open_file_cache; int /*<<< orphan*/  open_file_cache_errors; int /*<<< orphan*/  open_file_cache_valid; } ;
typedef  TYPE_5__ ngx_http_core_loc_conf_t ;
struct TYPE_18__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_EACCES ; 
 scalar_t__ NGX_ELOOP ; 
 scalar_t__ NGX_EMLINK ; 
 scalar_t__ NGX_ENOENT ; 
 scalar_t__ NGX_HTTP_FORBIDDEN ; 
 scalar_t__ NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_CRIT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_index_error (TYPE_4__*,TYPE_5__*,char*,scalar_t__) ; 
 scalar_t__ ngx_http_set_disable_symlinks (TYPE_4__*,TYPE_5__*,TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*,char*,...) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_3__*,int) ; 
 scalar_t__ ngx_open_cached_file (int /*<<< orphan*/ ,TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_index_test_dir(ngx_http_request_t *r, ngx_http_core_loc_conf_t *clcf,
    u_char *path, u_char *last)
{
    u_char                c;
    ngx_str_t             dir;
    ngx_open_file_info_t  of;

    c = *last;
    if (c != '/' || path == last) {
        /* "alias" without trailing slash */
        c = *(++last);
    }
    *last = '\0';

    dir.len = last - path;
    dir.data = path;

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "http index check dir: \"%V\"", &dir);

    ngx_memzero(&of, sizeof(ngx_open_file_info_t));

    of.test_dir = 1;
    of.test_only = 1;
    of.valid = clcf->open_file_cache_valid;
    of.errors = clcf->open_file_cache_errors;

    if (ngx_http_set_disable_symlinks(r, clcf, &dir, &of) != NGX_OK) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    if (ngx_open_cached_file(clcf->open_file_cache, &dir, &of, r->pool)
        != NGX_OK)
    {
        if (of.err) {

#if (NGX_HAVE_OPENAT)
            if (of.err == NGX_EMLINK
                || of.err == NGX_ELOOP)
            {
                return NGX_HTTP_FORBIDDEN;
            }
#endif

            if (of.err == NGX_ENOENT) {
                *last = c;
                return ngx_http_index_error(r, clcf, dir.data, NGX_ENOENT);
            }

            if (of.err == NGX_EACCES) {

                *last = c;

                /*
                 * ngx_http_index_test_dir() is called after the first index
                 * file testing has returned an error distinct from NGX_EACCES.
                 * This means that directory searching is allowed.
                 */

                return NGX_OK;
            }

            ngx_log_error(NGX_LOG_CRIT, r->connection->log, of.err,
                          "%s \"%s\" failed", of.failed, dir.data);
        }

        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    *last = c;

    if (of.is_dir) {
        return NGX_OK;
    }

    ngx_log_error(NGX_LOG_ALERT, r->connection->log, 0,
                  "\"%s\" is not a directory", dir.data);

    return NGX_HTTP_INTERNAL_SERVER_ERROR;
}