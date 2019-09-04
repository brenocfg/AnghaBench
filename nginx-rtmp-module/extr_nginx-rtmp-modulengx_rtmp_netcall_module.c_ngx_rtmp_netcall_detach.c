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
struct TYPE_4__ {int detached; } ;
typedef  TYPE_1__ ngx_rtmp_netcall_session_t ;
struct TYPE_5__ {TYPE_1__* data; } ;
typedef  TYPE_2__ ngx_connection_t ;

/* Variables and functions */

__attribute__((used)) static void
ngx_rtmp_netcall_detach(ngx_connection_t *cc)
{
    ngx_rtmp_netcall_session_t         *cs;

    cs = cc->data;
    cs->detached = 1;
}