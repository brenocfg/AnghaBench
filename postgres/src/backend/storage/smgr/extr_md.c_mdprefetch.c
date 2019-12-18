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
typedef  int off_t ;
struct TYPE_3__ {int /*<<< orphan*/  mdfd_vfd; } ;
typedef  int /*<<< orphan*/  SMgrRelation ;
typedef  TYPE_1__ MdfdVec ;
typedef  int /*<<< orphan*/  ForkNumber ;
typedef  int BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BLCKSZ ; 
 int /*<<< orphan*/  EXTENSION_FAIL ; 
 int /*<<< orphan*/  FilePrefetch (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int RELSEG_SIZE ; 
 int /*<<< orphan*/  WAIT_EVENT_DATA_FILE_PREFETCH ; 
 TYPE_1__* _mdfd_getseg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

void
mdprefetch(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum)
{
#ifdef USE_PREFETCH
	off_t		seekpos;
	MdfdVec    *v;

	v = _mdfd_getseg(reln, forknum, blocknum, false, EXTENSION_FAIL);

	seekpos = (off_t) BLCKSZ * (blocknum % ((BlockNumber) RELSEG_SIZE));

	Assert(seekpos < (off_t) BLCKSZ * RELSEG_SIZE);

	(void) FilePrefetch(v->mdfd_vfd, seekpos, BLCKSZ, WAIT_EVENT_DATA_FILE_PREFETCH);
#endif							/* USE_PREFETCH */
}