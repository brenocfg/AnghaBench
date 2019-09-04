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
typedef  int /*<<< orphan*/  ngx_stream_session_t ;
struct TYPE_4__ {TYPE_2__* data; } ;
typedef  TYPE_1__ ngx_event_t ;
struct TYPE_5__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ ngx_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_stream_core_run_phases (int /*<<< orphan*/ *) ; 

void
ngx_stream_session_handler(ngx_event_t *rev)
{
    ngx_connection_t      *c;
    ngx_stream_session_t  *s;

    c = rev->data;
    s = c->data;

    ngx_stream_core_run_phases(s);
}