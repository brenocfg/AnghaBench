#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_2__ {int NumRxUnicastOkInPeriod; int NumTxOkInPeriod; } ;
struct rtllib_device {scalar_t__ state; int /*<<< orphan*/  last_rx_ps_time; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* LeisurePSLeave ) (int /*<<< orphan*/ ) ;TYPE_1__ LinkDetectInfo; } ;

/* Variables and functions */
 scalar_t__ RTLLIB_LINKED ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtllib_rx_check_leave_lps(struct rtllib_device *ieee, u8 unicast,
				      u8 nr_subframes)
{
	if (unicast) {

		if (ieee->state == RTLLIB_LINKED) {
			if (((ieee->LinkDetectInfo.NumRxUnicastOkInPeriod +
			    ieee->LinkDetectInfo.NumTxOkInPeriod) > 8) ||
			    (ieee->LinkDetectInfo.NumRxUnicastOkInPeriod > 2)) {
				if (ieee->LeisurePSLeave)
					ieee->LeisurePSLeave(ieee->dev);
			}
		}
	}
	ieee->last_rx_ps_time = jiffies;
}