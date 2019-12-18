#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int mdfd_vfd; int mdfd_segno; } ;
struct TYPE_9__ {int* md_num_open_segs; TYPE_2__** md_seg_fds; } ;
typedef  TYPE_1__* SMgrRelation ;
typedef  TYPE_2__ MdfdVec ;
typedef  size_t ForkNumber ;
typedef  int BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int O_RDWR ; 
 int PG_BINARY ; 
 int PathNameOpenFile (char*,int) ; 
 scalar_t__ RELSEG_SIZE ; 
 int /*<<< orphan*/  _fdvec_resize (TYPE_1__*,size_t,int) ; 
 char* _mdfd_segpath (TYPE_1__*,size_t,int) ; 
 int _mdnblocks (TYPE_1__*,size_t,TYPE_2__*) ; 
 int /*<<< orphan*/  pfree (char*) ; 

__attribute__((used)) static MdfdVec *
_mdfd_openseg(SMgrRelation reln, ForkNumber forknum, BlockNumber segno,
			  int oflags)
{
	MdfdVec    *v;
	int			fd;
	char	   *fullpath;

	fullpath = _mdfd_segpath(reln, forknum, segno);

	/* open the file */
	fd = PathNameOpenFile(fullpath, O_RDWR | PG_BINARY | oflags);

	pfree(fullpath);

	if (fd < 0)
		return NULL;

	if (segno <= reln->md_num_open_segs[forknum])
		_fdvec_resize(reln, forknum, segno + 1);

	/* fill the entry */
	v = &reln->md_seg_fds[forknum][segno];
	v->mdfd_vfd = fd;
	v->mdfd_segno = segno;

	Assert(_mdnblocks(reln, forknum, v) <= ((BlockNumber) RELSEG_SIZE));

	/* all done */
	return v;
}