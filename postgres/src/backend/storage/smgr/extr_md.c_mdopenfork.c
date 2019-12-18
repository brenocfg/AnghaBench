#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ mdfd_segno; scalar_t__ mdfd_vfd; } ;
struct TYPE_8__ {scalar_t__* md_num_open_segs; TYPE_2__** md_seg_fds; int /*<<< orphan*/  smgr_rnode; } ;
typedef  TYPE_1__* SMgrRelation ;
typedef  TYPE_2__ MdfdVec ;
typedef  size_t ForkNumber ;
typedef  scalar_t__ File ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int EXTENSION_RETURN_NULL ; 
 scalar_t__ FILE_POSSIBLY_DELETED (int /*<<< orphan*/ ) ; 
 int O_RDWR ; 
 int PG_BINARY ; 
 scalar_t__ PathNameOpenFile (char*,int) ; 
 scalar_t__ RELSEG_SIZE ; 
 int /*<<< orphan*/  _fdvec_resize (TYPE_1__*,size_t,int) ; 
 scalar_t__ _mdnblocks (TYPE_1__*,size_t,TYPE_2__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* relpath (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static MdfdVec *
mdopenfork(SMgrRelation reln, ForkNumber forknum, int behavior)
{
	MdfdVec    *mdfd;
	char	   *path;
	File		fd;

	/* No work if already open */
	if (reln->md_num_open_segs[forknum] > 0)
		return &reln->md_seg_fds[forknum][0];

	path = relpath(reln->smgr_rnode, forknum);

	fd = PathNameOpenFile(path, O_RDWR | PG_BINARY);

	if (fd < 0)
	{
		if ((behavior & EXTENSION_RETURN_NULL) &&
			FILE_POSSIBLY_DELETED(errno))
		{
			pfree(path);
			return NULL;
		}
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not open file \"%s\": %m", path)));
	}

	pfree(path);

	_fdvec_resize(reln, forknum, 1);
	mdfd = &reln->md_seg_fds[forknum][0];
	mdfd->mdfd_vfd = fd;
	mdfd->mdfd_segno = 0;

	Assert(_mdnblocks(reln, forknum, mdfd) <= ((BlockNumber) RELSEG_SIZE));

	return mdfd;
}