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
typedef  int MultiXactStatus ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
#define  MultiXactStatusForKeyShare 133 
#define  MultiXactStatusForNoKeyUpdate 132 
#define  MultiXactStatusForShare 131 
#define  MultiXactStatusForUpdate 130 
#define  MultiXactStatusNoKeyUpdate 129 
#define  MultiXactStatusUpdate 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static char *
mxstatus_to_string(MultiXactStatus status)
{
	switch (status)
	{
		case MultiXactStatusForKeyShare:
			return "keysh";
		case MultiXactStatusForShare:
			return "sh";
		case MultiXactStatusForNoKeyUpdate:
			return "fornokeyupd";
		case MultiXactStatusForUpdate:
			return "forupd";
		case MultiXactStatusNoKeyUpdate:
			return "nokeyupd";
		case MultiXactStatusUpdate:
			return "upd";
		default:
			elog(ERROR, "unrecognized multixact status %d", status);
			return "";
	}
}