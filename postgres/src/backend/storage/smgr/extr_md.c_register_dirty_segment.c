#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  mdfd_vfd; int /*<<< orphan*/  mdfd_segno; } ;
struct TYPE_7__ {int /*<<< orphan*/  node; } ;
struct TYPE_8__ {TYPE_1__ smgr_rnode; } ;
typedef  TYPE_2__* SMgrRelation ;
typedef  TYPE_3__ MdfdVec ;
typedef  int /*<<< orphan*/  ForkNumber ;
typedef  int /*<<< orphan*/  FileTag ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FilePathName (int /*<<< orphan*/ ) ; 
 scalar_t__ FileSync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_MD_FILETAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegisterSyncRequest (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SYNC_REQUEST ; 
 int /*<<< orphan*/  SmgrIsTemp (TYPE_2__*) ; 
 int /*<<< orphan*/  WAIT_EVENT_DATA_FILE_SYNC ; 
 int /*<<< orphan*/  data_sync_elevel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 

__attribute__((used)) static void
register_dirty_segment(SMgrRelation reln, ForkNumber forknum, MdfdVec *seg)
{
	FileTag		tag;

	INIT_MD_FILETAG(tag, reln->smgr_rnode.node, forknum, seg->mdfd_segno);

	/* Temp relations should never be fsync'd */
	Assert(!SmgrIsTemp(reln));

	if (!RegisterSyncRequest(&tag, SYNC_REQUEST, false /* retryOnError */ ))
	{
		ereport(DEBUG1,
				(errmsg("could not forward fsync request because request queue is full")));

		if (FileSync(seg->mdfd_vfd, WAIT_EVENT_DATA_FILE_SYNC) < 0)
			ereport(data_sync_elevel(ERROR),
					(errcode_for_file_access(),
					 errmsg("could not fsync file \"%s\": %m",
							FilePathName(seg->mdfd_vfd))));
	}
}