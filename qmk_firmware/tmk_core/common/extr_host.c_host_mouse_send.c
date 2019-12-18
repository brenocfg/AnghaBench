#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  report_id; } ;
typedef  TYPE_1__ report_mouse_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* send_mouse ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  REPORT_ID_MOUSE ; 
 TYPE_4__* driver ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void host_mouse_send(report_mouse_t *report) {
    if (!driver) return;
#ifdef MOUSE_SHARED_EP
    report->report_id = REPORT_ID_MOUSE;
#endif
    (*driver->send_mouse)(report);
}