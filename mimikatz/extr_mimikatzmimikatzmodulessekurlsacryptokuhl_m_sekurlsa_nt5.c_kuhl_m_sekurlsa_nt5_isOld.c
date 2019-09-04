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
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ KULL_M_WIN_BUILD_2K3 ; 
 int /*<<< orphan*/  TRUE ; 

BOOL kuhl_m_sekurlsa_nt5_isOld(DWORD osBuildNumber, DWORD moduleTimeStamp)
{
	BOOL status = FALSE;
	if(osBuildNumber == KULL_M_WIN_BUILD_2K3)
	{
		if(moduleTimeStamp == 0x49901640) // up to date SP1 3290 - Mon Feb 09 12:40:48 2009 (WTF, a build number <, but timestamp >)
			status = TRUE;
		else if(moduleTimeStamp <= 0x45d70a62) // first SP2 3959 - Sat Feb 17 15:00:02 2007
			status = TRUE;
	}
	return status;
}