#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_10__ {int /*<<< orphan*/  log; scalar_t__ alloc; int /*<<< orphan*/ * data; void* spec_handler; int /*<<< orphan*/  post_tree_handler; int /*<<< orphan*/  pre_tree_handler; void* file_handler; int /*<<< orphan*/ * init_handler; } ;
typedef  TYPE_2__ ngx_tree_ctx_t ;
struct TYPE_11__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_12__ {TYPE_1__* connection; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_9__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_FILE_ERROR ; 
 scalar_t__ NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_NOT_FOUND ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_delete_dir (int /*<<< orphan*/ ) ; 
 char* ngx_delete_dir_n ; 
 scalar_t__ ngx_delete_file (int /*<<< orphan*/ ) ; 
 char* ngx_delete_file_n ; 
 int /*<<< orphan*/  ngx_errno ; 
 int /*<<< orphan*/  ngx_http_dav_delete_dir ; 
 void* ngx_http_dav_delete_file ; 
 scalar_t__ ngx_http_dav_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_dav_noop ; 
 scalar_t__ ngx_walk_tree (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_dav_delete_path(ngx_http_request_t *r, ngx_str_t *path, ngx_uint_t dir)
{
    char            *failed;
    ngx_tree_ctx_t   tree;

    if (dir) {

        tree.init_handler = NULL;
        tree.file_handler = ngx_http_dav_delete_file;
        tree.pre_tree_handler = ngx_http_dav_noop;
        tree.post_tree_handler = ngx_http_dav_delete_dir;
        tree.spec_handler = ngx_http_dav_delete_file;
        tree.data = NULL;
        tree.alloc = 0;
        tree.log = r->connection->log;

        /* TODO: 207 */

        if (ngx_walk_tree(&tree, path) != NGX_OK) {
            return NGX_HTTP_INTERNAL_SERVER_ERROR;
        }

        if (ngx_delete_dir(path->data) != NGX_FILE_ERROR) {
            return NGX_OK;
        }

        failed = ngx_delete_dir_n;

    } else {

        if (ngx_delete_file(path->data) != NGX_FILE_ERROR) {
            return NGX_OK;
        }

        failed = ngx_delete_file_n;
    }

    return ngx_http_dav_error(r->connection->log, ngx_errno,
                              NGX_HTTP_NOT_FOUND, failed, path->data);
}