#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ip; TYPE_1__* request; } ;
typedef  TYPE_2__ ngx_http_script_engine_t ;
struct TYPE_4__ {scalar_t__ uri_changed; } ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_http_script_exit ; 

void
ngx_http_script_break_code(ngx_http_script_engine_t *e)
{
    e->request->uri_changed = 0;

    e->ip = ngx_http_script_exit;
}