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
typedef  int /*<<< orphan*/  uint16 ;
typedef  int /*<<< orphan*/  XLTW_Oper ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  MultiXactStatus ;
typedef  int /*<<< orphan*/  MultiXactId ;
typedef  int /*<<< orphan*/  ItemPointer ;

/* Variables and functions */
 int /*<<< orphan*/  Do_MultiXactIdWait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
MultiXactIdWait(MultiXactId multi, MultiXactStatus status, uint16 infomask,
				Relation rel, ItemPointer ctid, XLTW_Oper oper,
				int *remaining)
{
	(void) Do_MultiXactIdWait(multi, status, infomask, false,
							  rel, ctid, oper, remaining);
}