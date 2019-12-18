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
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  RM_XLOG_ID ; 
 int /*<<< orphan*/  XLOG_NEXTOID ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int) ; 

void
XLogPutNextOid(Oid nextOid)
{
	XLogBeginInsert();
	XLogRegisterData((char *) (&nextOid), sizeof(Oid));
	(void) XLogInsert(RM_XLOG_ID, XLOG_NEXTOID);

	/*
	 * We need not flush the NEXTOID record immediately, because any of the
	 * just-allocated OIDs could only reach disk as part of a tuple insert or
	 * update that would have its own XLOG record that must follow the NEXTOID
	 * record.  Therefore, the standard buffer LSN interlock applied to those
	 * records will ensure no such OID reaches disk before the NEXTOID record
	 * does.
	 *
	 * Note, however, that the above statement only covers state "within" the
	 * database.  When we use a generated OID as a file or directory name, we
	 * are in a sense violating the basic WAL rule, because that filesystem
	 * change may reach disk before the NEXTOID WAL record does.  The impact
	 * of this is that if a database crash occurs immediately afterward, we
	 * might after restart re-generate the same OID and find that it conflicts
	 * with the leftover file or directory.  But since for safety's sake we
	 * always loop until finding a nonconflicting filename, this poses no real
	 * problem in practice. See pgsql-hackers discussion 27-Sep-2006.
	 */
}