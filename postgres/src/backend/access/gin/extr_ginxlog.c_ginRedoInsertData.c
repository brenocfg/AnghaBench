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
typedef  int /*<<< orphan*/  ginxlogRecompressDataLeaf ;
struct TYPE_2__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  newitem; } ;
typedef  TYPE_1__ ginxlogInsertDataInternal ;
typedef  int /*<<< orphan*/  PostingItem ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GinDataPageAddPostingItem (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GinDataPageGetPostingItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GinPageIsLeaf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PostingItemSetBlockNumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ginRedoRecompress (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ginRedoInsertData(Buffer buffer, bool isLeaf, BlockNumber rightblkno, void *rdata)
{
	Page		page = BufferGetPage(buffer);

	if (isLeaf)
	{
		ginxlogRecompressDataLeaf *data = (ginxlogRecompressDataLeaf *) rdata;

		Assert(GinPageIsLeaf(page));

		ginRedoRecompress(page, data);
	}
	else
	{
		ginxlogInsertDataInternal *data = (ginxlogInsertDataInternal *) rdata;
		PostingItem *oldpitem;

		Assert(!GinPageIsLeaf(page));

		/* update link to right page after split */
		oldpitem = GinDataPageGetPostingItem(page, data->offset);
		PostingItemSetBlockNumber(oldpitem, rightblkno);

		GinDataPageAddPostingItem(page, &data->newitem, data->offset);
	}
}