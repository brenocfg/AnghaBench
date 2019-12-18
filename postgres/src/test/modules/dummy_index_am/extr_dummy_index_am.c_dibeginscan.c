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
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  IndexScanDesc ;

/* Variables and functions */
 int /*<<< orphan*/  RelationGetIndexScan (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static IndexScanDesc
dibeginscan(Relation r, int nkeys, int norderbys)
{
	IndexScanDesc scan;

	/* Let's pretend we are doing something */
	scan = RelationGetIndexScan(r, nkeys, norderbys);
	return scan;
}