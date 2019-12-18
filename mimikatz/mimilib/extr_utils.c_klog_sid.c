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
typedef  scalar_t__ PSID ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ConvertSidToStringSid (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  klog (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void klog_sid(FILE * logfile, PSID pSid)
{
	LPWSTR stringSid;
	if(pSid && ConvertSidToStringSid(pSid, &stringSid))
	{
		klog(logfile, L"%s", stringSid);
		LocalFree(stringSid);
	}
}