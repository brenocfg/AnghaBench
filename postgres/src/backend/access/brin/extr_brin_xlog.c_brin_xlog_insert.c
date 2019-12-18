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
typedef  int /*<<< orphan*/  xl_brin_insert ;
typedef  int /*<<< orphan*/  XLogReaderState ;

/* Variables and functions */
 scalar_t__ XLogRecGetData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brin_xlog_insert_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
brin_xlog_insert(XLogReaderState *record)
{
	xl_brin_insert *xlrec = (xl_brin_insert *) XLogRecGetData(record);

	brin_xlog_insert_update(record, xlrec);
}