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
struct TYPE_6__ {int /*<<< orphan*/  mdfd_vfd; } ;
struct TYPE_5__ {int* md_num_open_segs; TYPE_2__** md_seg_fds; } ;
typedef  TYPE_1__* SMgrRelation ;
typedef  TYPE_2__ MdfdVec ;
typedef  size_t ForkNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FilePathName (int /*<<< orphan*/ ) ; 
 scalar_t__ FileSync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WAIT_EVENT_DATA_FILE_IMMEDIATE_SYNC ; 
 int /*<<< orphan*/  data_sync_elevel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdnblocks (TYPE_1__*,size_t) ; 

void
mdimmedsync(SMgrRelation reln, ForkNumber forknum)
{
	int			segno;

	/*
	 * NOTE: mdnblocks makes sure we have opened all active segments, so that
	 * fsync loop will get them all!
	 */
	mdnblocks(reln, forknum);

	segno = reln->md_num_open_segs[forknum];

	while (segno > 0)
	{
		MdfdVec    *v = &reln->md_seg_fds[forknum][segno - 1];

		if (FileSync(v->mdfd_vfd, WAIT_EVENT_DATA_FILE_IMMEDIATE_SYNC) < 0)
			ereport(data_sync_elevel(ERROR),
					(errcode_for_file_access(),
					 errmsg("could not fsync file \"%s\": %m",
							FilePathName(v->mdfd_vfd))));
		segno--;
	}
}