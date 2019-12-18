#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  dbNode; int /*<<< orphan*/  spcNode; } ;
struct TYPE_10__ {TYPE_1__ node; } ;
struct TYPE_9__ {scalar_t__ mdfd_segno; scalar_t__ mdfd_vfd; } ;
struct TYPE_8__ {scalar_t__* md_num_open_segs; TYPE_3__** md_seg_fds; TYPE_4__ smgr_rnode; } ;
typedef  TYPE_2__* SMgrRelation ;
typedef  TYPE_3__ MdfdVec ;
typedef  size_t ForkNumber ;
typedef  scalar_t__ File ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_RDWR ; 
 int PG_BINARY ; 
 scalar_t__ PathNameOpenFile (char*,int) ; 
 int /*<<< orphan*/  TablespaceCreateDbspace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _fdvec_resize (TYPE_2__*,size_t,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 int errno ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* relpath (TYPE_4__,size_t) ; 

void
mdcreate(SMgrRelation reln, ForkNumber forkNum, bool isRedo)
{
	MdfdVec    *mdfd;
	char	   *path;
	File		fd;

	if (isRedo && reln->md_num_open_segs[forkNum] > 0)
		return;					/* created and opened already... */

	Assert(reln->md_num_open_segs[forkNum] == 0);

	/*
	 * We may be using the target table space for the first time in this
	 * database, so create a per-database subdirectory if needed.
	 *
	 * XXX this is a fairly ugly violation of module layering, but this seems
	 * to be the best place to put the check.  Maybe TablespaceCreateDbspace
	 * should be here and not in commands/tablespace.c?  But that would imply
	 * importing a lot of stuff that smgr.c oughtn't know, either.
	 */
	TablespaceCreateDbspace(reln->smgr_rnode.node.spcNode,
							reln->smgr_rnode.node.dbNode,
							isRedo);

	path = relpath(reln->smgr_rnode, forkNum);

	fd = PathNameOpenFile(path, O_RDWR | O_CREAT | O_EXCL | PG_BINARY);

	if (fd < 0)
	{
		int			save_errno = errno;

		if (isRedo)
			fd = PathNameOpenFile(path, O_RDWR | PG_BINARY);
		if (fd < 0)
		{
			/* be sure to report the error reported by create, not open */
			errno = save_errno;
			ereport(ERROR,
					(errcode_for_file_access(),
					 errmsg("could not create file \"%s\": %m", path)));
		}
	}

	pfree(path);

	_fdvec_resize(reln, forkNum, 1);
	mdfd = &reln->md_seg_fds[forkNum][0];
	mdfd->mdfd_vfd = fd;
	mdfd->mdfd_segno = 0;
}