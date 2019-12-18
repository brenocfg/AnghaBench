#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_8__ {int /*<<< orphan*/  log; int /*<<< orphan*/  access; TYPE_4__* data; } ;
typedef  TYPE_2__ ngx_tree_ctx_t ;
struct TYPE_9__ {size_t len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_3__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_7__ {size_t len; int /*<<< orphan*/  data; } ;
struct TYPE_10__ {size_t len; TYPE_1__ path; } ;
typedef  TYPE_4__ ngx_http_dav_copy_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ABORT ; 
 scalar_t__ NGX_FILE_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/ * ngx_alloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_cpymem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_cpystrn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ ngx_create_dir (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_create_dir_n ; 
 int /*<<< orphan*/  ngx_dir_access (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_errno ; 
 int /*<<< orphan*/  ngx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_dav_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_http_dav_copy_dir(ngx_tree_ctx_t *ctx, ngx_str_t *path)
{
    u_char                   *p, *dir;
    size_t                    len;
    ngx_http_dav_copy_ctx_t  *copy;

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, ctx->log, 0,
                   "http copy dir: \"%s\"", path->data);

    copy = ctx->data;

    len = copy->path.len + path->len;

    dir = ngx_alloc(len + 1, ctx->log);
    if (dir == NULL) {
        return NGX_ABORT;
    }

    p = ngx_cpymem(dir, copy->path.data, copy->path.len);
    (void) ngx_cpystrn(p, path->data + copy->len, path->len - copy->len + 1);

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, ctx->log, 0,
                   "http copy dir to: \"%s\"", dir);

    if (ngx_create_dir(dir, ngx_dir_access(ctx->access)) == NGX_FILE_ERROR) {
        (void) ngx_http_dav_error(ctx->log, ngx_errno, 0, ngx_create_dir_n,
                                  dir);
    }

    ngx_free(dir);

    return NGX_OK;
}