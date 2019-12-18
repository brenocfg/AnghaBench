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

/* Variables and functions */
 int Q_QUOTAOFF ; 
 int Q_QUOTAON ; 
 int Q_XQUOTAOFF ; 
 int Q_XQUOTAON ; 

__attribute__((used)) static bool quotactl_cmd_onoff(int cmd)
{
	return (cmd == Q_QUOTAON) || (cmd == Q_QUOTAOFF) ||
		 (cmd == Q_XQUOTAON) || (cmd == Q_XQUOTAOFF);
}