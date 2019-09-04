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
struct TYPE_4__ {scalar_t__ flags; scalar_t__ length; } ;
union iwreq_data {TYPE_1__ data; } ;
struct TYPE_5__ {scalar_t__ scan_timestamp; int /*<<< orphan*/  dev; } ;
typedef  TYPE_2__ local_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIOCGIWSCAN ; 
 int /*<<< orphan*/  wireless_send_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union iwreq_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hostap_report_scan_complete(local_info_t *local)
{
	union iwreq_data wrqu;

	/* Inform user space about new scan results (just empty event,
	 * SIOCGIWSCAN can be used to fetch data */
	wrqu.data.length = 0;
	wrqu.data.flags = 0;
	wireless_send_event(local->dev, SIOCGIWSCAN, &wrqu, NULL);

	/* Allow SIOCGIWSCAN handling to occur since we have received
	 * scanning result */
	local->scan_timestamp = 0;
}