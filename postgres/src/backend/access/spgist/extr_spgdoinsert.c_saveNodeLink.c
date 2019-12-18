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
struct TYPE_3__ {int /*<<< orphan*/  buffer; int /*<<< orphan*/  node; int /*<<< orphan*/  offnum; int /*<<< orphan*/  page; } ;
typedef  scalar_t__ SpGistInnerTuple ;
typedef  TYPE_1__ SPPageDesc ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spgUpdateNodeLink (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
saveNodeLink(Relation index, SPPageDesc *parent,
			 BlockNumber blkno, OffsetNumber offnum)
{
	SpGistInnerTuple innerTuple;

	innerTuple = (SpGistInnerTuple) PageGetItem(parent->page,
												PageGetItemId(parent->page, parent->offnum));

	spgUpdateNodeLink(innerTuple, parent->node, blkno, offnum);

	MarkBufferDirty(parent->buffer);
}