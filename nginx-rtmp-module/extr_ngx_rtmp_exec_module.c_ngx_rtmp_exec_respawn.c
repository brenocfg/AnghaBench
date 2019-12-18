#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_rtmp_exec_t ;
struct TYPE_3__ {scalar_t__ data; } ;
typedef  TYPE_1__ ngx_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_rtmp_exec_run (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ngx_rtmp_exec_respawn(ngx_event_t *ev)
{
    ngx_rtmp_exec_run((ngx_rtmp_exec_t *) ev->data);
}