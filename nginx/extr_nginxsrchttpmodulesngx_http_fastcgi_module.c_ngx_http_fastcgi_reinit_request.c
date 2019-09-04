#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_8__ {scalar_t__ state; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_9__ {TYPE_1__* split_parts; scalar_t__ large_stderr; scalar_t__ fastcgi_stdout; int /*<<< orphan*/  state; } ;
typedef  TYPE_3__ ngx_http_fastcgi_ctx_t ;
struct TYPE_7__ {scalar_t__ nelts; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_http_fastcgi_module ; 
 int /*<<< orphan*/  ngx_http_fastcgi_st_version ; 
 TYPE_3__* ngx_http_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_fastcgi_reinit_request(ngx_http_request_t *r)
{
    ngx_http_fastcgi_ctx_t  *f;

    f = ngx_http_get_module_ctx(r, ngx_http_fastcgi_module);

    if (f == NULL) {
        return NGX_OK;
    }

    f->state = ngx_http_fastcgi_st_version;
    f->fastcgi_stdout = 0;
    f->large_stderr = 0;

    if (f->split_parts) {
        f->split_parts->nelts = 0;
    }

    r->state = 0;

    return NGX_OK;
}