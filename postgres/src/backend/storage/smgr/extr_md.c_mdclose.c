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
struct TYPE_6__ {int mdfd_vfd; } ;
struct TYPE_5__ {int* md_num_open_segs; TYPE_2__** md_seg_fds; } ;
typedef  TYPE_1__* SMgrRelation ;
typedef  TYPE_2__ MdfdVec ;
typedef  size_t ForkNumber ;

/* Variables and functions */
 int /*<<< orphan*/  FileClose (int) ; 
 int /*<<< orphan*/  _fdvec_resize (TYPE_1__*,size_t,int /*<<< orphan*/ ) ; 

void
mdclose(SMgrRelation reln, ForkNumber forknum)
{
	int			nopensegs = reln->md_num_open_segs[forknum];

	/* No work if already closed */
	if (nopensegs == 0)
		return;

	/* close segments starting from the end */
	while (nopensegs > 0)
	{
		MdfdVec    *v = &reln->md_seg_fds[forknum][nopensegs - 1];

		/* if not closed already */
		if (v->mdfd_vfd >= 0)
		{
			FileClose(v->mdfd_vfd);
			v->mdfd_vfd = -1;
		}

		nopensegs--;
	}

	/* resize just once, avoids pointless reallocations */
	_fdvec_resize(reln, forknum, 0);
}