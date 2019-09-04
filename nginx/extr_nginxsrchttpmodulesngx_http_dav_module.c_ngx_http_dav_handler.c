#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_15__ {int /*<<< orphan*/  content_range; } ;
struct TYPE_14__ {char* data; int /*<<< orphan*/  len; } ;
struct TYPE_17__ {int method; int request_body_in_file_only; int request_body_in_persistent_file; int request_body_in_clean_file; int request_body_file_group_access; int /*<<< orphan*/  request_body_file_log_level; TYPE_3__* connection; TYPE_2__ headers_in; TYPE_1__ uri; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_18__ {int methods; } ;
typedef  TYPE_5__ ngx_http_dav_loc_conf_t ;
struct TYPE_16__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DECLINED ; 
 int /*<<< orphan*/  NGX_DONE ; 
 int /*<<< orphan*/  NGX_HTTP_CONFLICT ; 
#define  NGX_HTTP_COPY 132 
#define  NGX_HTTP_DELETE 131 
#define  NGX_HTTP_MKCOL 130 
#define  NGX_HTTP_MOVE 129 
 int /*<<< orphan*/  NGX_HTTP_NOT_IMPLEMENTED ; 
#define  NGX_HTTP_PUT 128 
 int /*<<< orphan*/  NGX_HTTP_SPECIAL_RESPONSE ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  ngx_http_dav_copy_move_handler (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_dav_delete_handler (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_dav_mkcol_handler (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_http_dav_module ; 
 int /*<<< orphan*/  ngx_http_dav_put_handler ; 
 TYPE_5__* ngx_http_get_module_loc_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_read_client_request_body (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_dav_handler(ngx_http_request_t *r)
{
    ngx_int_t                 rc;
    ngx_http_dav_loc_conf_t  *dlcf;

    dlcf = ngx_http_get_module_loc_conf(r, ngx_http_dav_module);

    if (!(r->method & dlcf->methods)) {
        return NGX_DECLINED;
    }

    switch (r->method) {

    case NGX_HTTP_PUT:

        if (r->uri.data[r->uri.len - 1] == '/') {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                          "cannot PUT to a collection");
            return NGX_HTTP_CONFLICT;
        }

        if (r->headers_in.content_range) {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                          "PUT with range is unsupported");
            return NGX_HTTP_NOT_IMPLEMENTED;
        }

        r->request_body_in_file_only = 1;
        r->request_body_in_persistent_file = 1;
        r->request_body_in_clean_file = 1;
        r->request_body_file_group_access = 1;
        r->request_body_file_log_level = 0;

        rc = ngx_http_read_client_request_body(r, ngx_http_dav_put_handler);

        if (rc >= NGX_HTTP_SPECIAL_RESPONSE) {
            return rc;
        }

        return NGX_DONE;

    case NGX_HTTP_DELETE:

        return ngx_http_dav_delete_handler(r);

    case NGX_HTTP_MKCOL:

        return ngx_http_dav_mkcol_handler(r, dlcf);

    case NGX_HTTP_COPY:

        return ngx_http_dav_copy_move_handler(r);

    case NGX_HTTP_MOVE:

        return ngx_http_dav_copy_move_handler(r);
    }

    return NGX_DECLINED;
}