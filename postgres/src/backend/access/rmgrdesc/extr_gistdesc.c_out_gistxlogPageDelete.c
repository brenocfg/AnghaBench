#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  downlinkOffset; int /*<<< orphan*/  deleteXid; } ;
typedef  TYPE_1__ gistxlogPageDelete ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  EpochFromFullTransactionId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XidFromFullTransactionId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
out_gistxlogPageDelete(StringInfo buf, gistxlogPageDelete *xlrec)
{
	appendStringInfo(buf, "deleteXid %u:%u; downlink %u",
					 EpochFromFullTransactionId(xlrec->deleteXid),
					 XidFromFullTransactionId(xlrec->deleteXid),
					 xlrec->downlinkOffset);
}