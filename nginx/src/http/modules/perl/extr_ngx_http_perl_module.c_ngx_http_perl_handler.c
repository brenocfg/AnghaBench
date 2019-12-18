#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_6__ {TYPE_1__* main; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_5__ {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DONE ; 
 int /*<<< orphan*/  ngx_http_perl_handle_request (TYPE_2__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_perl_handler(ngx_http_request_t *r)
{
    r->main->count++;

    ngx_http_perl_handle_request(r);

    return NGX_DONE;
}