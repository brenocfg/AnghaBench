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
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  NotifyStmt ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conditionname ; 
 int /*<<< orphan*/  payload ; 

__attribute__((used)) static void
_outNotifyStmt(StringInfo str, const NotifyStmt *node)
{
	WRITE_NODE_TYPE("NOTIFY");

	WRITE_STRING_FIELD(conditionname);
	WRITE_STRING_FIELD(payload);
}