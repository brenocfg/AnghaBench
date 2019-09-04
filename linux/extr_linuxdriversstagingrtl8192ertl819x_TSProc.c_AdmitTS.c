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
typedef  scalar_t__ u32 ;
struct ts_common_info {int /*<<< orphan*/  InactTimer; int /*<<< orphan*/  SetupTimer; } ;
struct rtllib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (scalar_t__) ; 

__attribute__((used)) static void AdmitTS(struct rtllib_device *ieee,
		    struct ts_common_info *pTsCommonInfo, u32 InactTime)
{
	del_timer_sync(&pTsCommonInfo->SetupTimer);
	del_timer_sync(&pTsCommonInfo->InactTimer);

	if (InactTime != 0)
		mod_timer(&pTsCommonInfo->InactTimer, jiffies +
			  msecs_to_jiffies(InactTime));
}