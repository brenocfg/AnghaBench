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
struct TYPE_2__ {int flags; } ;
typedef  TYPE_1__ ginxlogSplit ;
typedef  int /*<<< orphan*/  XLogReaderState ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 scalar_t__ BLK_RESTORED ; 
 int /*<<< orphan*/  ERROR ; 
 int GIN_INSERT_ISLEAF ; 
 int GIN_SPLIT_ROOT ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 scalar_t__ XLogReadBufferForRedo (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ XLogRecGetData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ginRedoClearIncompleteSplit (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
ginRedoSplit(XLogReaderState *record)
{
	ginxlogSplit *data = (ginxlogSplit *) XLogRecGetData(record);
	Buffer		lbuffer,
				rbuffer,
				rootbuf;
	bool		isLeaf = (data->flags & GIN_INSERT_ISLEAF) != 0;
	bool		isRoot = (data->flags & GIN_SPLIT_ROOT) != 0;

	/*
	 * First clear incomplete-split flag on child page if this finishes a
	 * split
	 */
	if (!isLeaf)
		ginRedoClearIncompleteSplit(record, 3);

	if (XLogReadBufferForRedo(record, 0, &lbuffer) != BLK_RESTORED)
		elog(ERROR, "GIN split record did not contain a full-page image of left page");

	if (XLogReadBufferForRedo(record, 1, &rbuffer) != BLK_RESTORED)
		elog(ERROR, "GIN split record did not contain a full-page image of right page");

	if (isRoot)
	{
		if (XLogReadBufferForRedo(record, 2, &rootbuf) != BLK_RESTORED)
			elog(ERROR, "GIN split record did not contain a full-page image of root page");
		UnlockReleaseBuffer(rootbuf);
	}

	UnlockReleaseBuffer(rbuffer);
	UnlockReleaseBuffer(lbuffer);
}