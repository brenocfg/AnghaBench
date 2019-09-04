#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ntp_synced () ; 
 scalar_t__ sync_cmos_clock () ; 
 int /*<<< orphan*/  sync_rtc_clock () ; 

__attribute__((used)) static void sync_hw_clock(struct work_struct *work)
{
	if (!ntp_synced())
		return;

	if (sync_cmos_clock())
		return;

	sync_rtc_clock();
}