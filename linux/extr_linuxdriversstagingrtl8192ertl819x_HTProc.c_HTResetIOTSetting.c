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
struct rt_hi_throughput {scalar_t__ IOTRaFunc; int /*<<< orphan*/  IOTPeer; scalar_t__ IOTAction; } ;

/* Variables and functions */
 int /*<<< orphan*/  HT_IOT_PEER_UNKNOWN ; 

void HTResetIOTSetting(struct rt_hi_throughput *pHTInfo)
{
	pHTInfo->IOTAction = 0;
	pHTInfo->IOTPeer = HT_IOT_PEER_UNKNOWN;
	pHTInfo->IOTRaFunc = 0;
}