#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  write; } ;
typedef  TYPE_1__ ngx_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_stream_proxy_process_connection (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ngx_stream_proxy_downstream_handler(ngx_event_t *ev)
{
    ngx_stream_proxy_process_connection(ev, ev->write);
}