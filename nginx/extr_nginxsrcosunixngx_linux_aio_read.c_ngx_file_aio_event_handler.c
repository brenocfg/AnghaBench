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
struct TYPE_7__ {int /*<<< orphan*/  log; TYPE_3__* data; } ;
typedef  TYPE_2__ ngx_event_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* handler ) (TYPE_2__*) ;TYPE_1__* file; int /*<<< orphan*/  fd; } ;
typedef  TYPE_3__ ngx_event_aio_t ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_CORE ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void
ngx_file_aio_event_handler(ngx_event_t *ev)
{
    ngx_event_aio_t  *aio;

    aio = ev->data;

    ngx_log_debug2(NGX_LOG_DEBUG_CORE, ev->log, 0,
                   "aio event handler fd:%d %V", aio->fd, &aio->file->name);

    aio->handler(ev);
}