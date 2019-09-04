#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_7__ {int valid; int /*<<< orphan*/  data; scalar_t__ not_found; scalar_t__ no_cacheable; int /*<<< orphan*/  len; } ;
typedef  TYPE_2__ ngx_http_variable_value_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
typedef  int /*<<< orphan*/  ngx_http_fastcgi_loc_conf_t ;
struct TYPE_6__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct TYPE_8__ {TYPE_1__ path_info; } ;
typedef  TYPE_3__ ngx_http_fastcgi_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_http_fastcgi_module ; 
 TYPE_3__* ngx_http_fastcgi_split (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_http_get_module_loc_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_fastcgi_path_info_variable(ngx_http_request_t *r,
    ngx_http_variable_value_t *v, uintptr_t data)
{
    ngx_http_fastcgi_ctx_t       *f;
    ngx_http_fastcgi_loc_conf_t  *flcf;

    flcf = ngx_http_get_module_loc_conf(r, ngx_http_fastcgi_module);

    f = ngx_http_fastcgi_split(r, flcf);

    if (f == NULL) {
        return NGX_ERROR;
    }

    v->len = f->path_info.len;
    v->valid = 1;
    v->no_cacheable = 0;
    v->not_found = 0;
    v->data = f->path_info.data;

    return NGX_OK;
}