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
typedef  int off_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_9__ {TYPE_2__* upstream; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_10__ {scalar_t__ keep_conn; } ;
typedef  TYPE_4__ ngx_http_fastcgi_loc_conf_t ;
typedef  int /*<<< orphan*/  ngx_http_fastcgi_header_t ;
struct TYPE_8__ {TYPE_1__* pipe; } ;
struct TYPE_7__ {int length; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_http_fastcgi_module ; 
 TYPE_4__* ngx_http_get_module_loc_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_fastcgi_input_filter_init(void *data)
{
    ngx_http_request_t           *r = data;
    ngx_http_fastcgi_loc_conf_t  *flcf;

    flcf = ngx_http_get_module_loc_conf(r, ngx_http_fastcgi_module);

    r->upstream->pipe->length = flcf->keep_conn ?
                                (off_t) sizeof(ngx_http_fastcgi_header_t) : -1;

    return NGX_OK;
}