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
typedef  int LockClauseStrength ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
#define  LCS_FORKEYSHARE 132 
#define  LCS_FORNOKEYUPDATE 131 
#define  LCS_FORSHARE 130 
#define  LCS_FORUPDATE 129 
#define  LCS_NONE 128 

const char *
LCS_asString(LockClauseStrength strength)
{
	switch (strength)
	{
		case LCS_NONE:
			Assert(false);
			break;
		case LCS_FORKEYSHARE:
			return "FOR KEY SHARE";
		case LCS_FORSHARE:
			return "FOR SHARE";
		case LCS_FORNOKEYUPDATE:
			return "FOR NO KEY UPDATE";
		case LCS_FORUPDATE:
			return "FOR UPDATE";
	}
	return "FOR some";			/* shouldn't happen */
}