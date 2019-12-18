#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ ginxlogCreatePostingTree ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_7__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_2__ XLogReaderState ;
typedef  scalar_t__ Page ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 int GIN_COMPRESSED ; 
 int GIN_DATA ; 
 int GIN_LEAF ; 
 int /*<<< orphan*/  GinDataLeafPageGetPostingList (scalar_t__) ; 
 int /*<<< orphan*/  GinDataPageSetDataSize (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GinInitBuffer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogInitBufferForRedo (TYPE_2__*,int /*<<< orphan*/ ) ; 
 char* XLogRecGetData (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ginRedoCreatePTree(XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	ginxlogCreatePostingTree *data = (ginxlogCreatePostingTree *) XLogRecGetData(record);
	char	   *ptr;
	Buffer		buffer;
	Page		page;

	buffer = XLogInitBufferForRedo(record, 0);
	page = (Page) BufferGetPage(buffer);

	GinInitBuffer(buffer, GIN_DATA | GIN_LEAF | GIN_COMPRESSED);

	ptr = XLogRecGetData(record) + sizeof(ginxlogCreatePostingTree);

	/* Place page data */
	memcpy(GinDataLeafPageGetPostingList(page), ptr, data->size);

	GinDataPageSetDataSize(page, data->size);

	PageSetLSN(page, lsn);

	MarkBufferDirty(buffer);
	UnlockReleaseBuffer(buffer);
}