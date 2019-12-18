#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  walinfolen; int /*<<< orphan*/  walinfo; } ;
typedef  TYPE_1__ disassembledLeaf ;
struct TYPE_6__ {int /*<<< orphan*/  isBuild; int /*<<< orphan*/  index; } ;
typedef  int /*<<< orphan*/  GinBtreeStack ;
typedef  TYPE_2__* GinBtree ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBufData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dataPlaceToPageLeafRecompress (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void
dataExecPlaceToPageLeaf(GinBtree btree, Buffer buf, GinBtreeStack *stack,
						void *insertdata, void *ptp_workspace)
{
	disassembledLeaf *leaf = (disassembledLeaf *) ptp_workspace;

	/* Apply changes to page */
	dataPlaceToPageLeafRecompress(buf, leaf);

	/* If needed, register WAL data built by computeLeafRecompressWALData */
	if (RelationNeedsWAL(btree->index) && !btree->isBuild)
	{
		XLogRegisterBufData(0, leaf->walinfo, leaf->walinfolen);
	}
}