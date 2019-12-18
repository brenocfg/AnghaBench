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
struct TYPE_2__ {int /*<<< orphan*/  rp_name; int /*<<< orphan*/  rp_time; } ;
typedef  TYPE_1__ xl_restore_point ;
typedef  int /*<<< orphan*/  uint32 ;
typedef  int XLogRecPtr ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentTimestamp () ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  MAXFNAMELEN ; 
 int /*<<< orphan*/  RM_XLOG_ID ; 
 int /*<<< orphan*/  XLOG_RESTORE_POINT ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

XLogRecPtr
XLogRestorePoint(const char *rpName)
{
	XLogRecPtr	RecPtr;
	xl_restore_point xlrec;

	xlrec.rp_time = GetCurrentTimestamp();
	strlcpy(xlrec.rp_name, rpName, MAXFNAMELEN);

	XLogBeginInsert();
	XLogRegisterData((char *) &xlrec, sizeof(xl_restore_point));

	RecPtr = XLogInsert(RM_XLOG_ID, XLOG_RESTORE_POINT);

	ereport(LOG,
			(errmsg("restore point \"%s\" created at %X/%X",
					rpName, (uint32) (RecPtr >> 32), (uint32) RecPtr)));

	return RecPtr;
}