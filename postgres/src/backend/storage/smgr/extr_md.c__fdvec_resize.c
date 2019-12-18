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
struct TYPE_3__ {int* md_num_open_segs; int /*<<< orphan*/ ** md_seg_fds; } ;
typedef  TYPE_1__* SMgrRelation ;
typedef  int /*<<< orphan*/  MdfdVec ;
typedef  size_t ForkNumber ;

/* Variables and functions */
 int /*<<< orphan*/  MdCxt ; 
 int /*<<< orphan*/ * MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * repalloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
_fdvec_resize(SMgrRelation reln,
			  ForkNumber forknum,
			  int nseg)
{
	if (nseg == 0)
	{
		if (reln->md_num_open_segs[forknum] > 0)
		{
			pfree(reln->md_seg_fds[forknum]);
			reln->md_seg_fds[forknum] = NULL;
		}
	}
	else if (reln->md_num_open_segs[forknum] == 0)
	{
		reln->md_seg_fds[forknum] =
			MemoryContextAlloc(MdCxt, sizeof(MdfdVec) * nseg);
	}
	else
	{
		/*
		 * It doesn't seem worthwhile complicating the code by having a more
		 * aggressive growth strategy here; the number of segments doesn't
		 * grow that fast, and the memory context internally will sometimes
		 * avoid doing an actual reallocation.
		 */
		reln->md_seg_fds[forknum] =
			repalloc(reln->md_seg_fds[forknum],
					 sizeof(MdfdVec) * nseg);
	}

	reln->md_num_open_segs[forknum] = nseg;
}