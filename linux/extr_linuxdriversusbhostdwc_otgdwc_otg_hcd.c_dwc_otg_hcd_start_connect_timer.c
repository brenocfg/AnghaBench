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
struct TYPE_3__ {int /*<<< orphan*/  conn_timer; } ;
typedef  TYPE_1__ dwc_otg_hcd_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_TIMER_SCHEDULE (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dwc_otg_hcd_start_connect_timer(dwc_otg_hcd_t * hcd)
{
	DWC_TIMER_SCHEDULE(hcd->conn_timer, 10000 /* 10 secs */ );
}