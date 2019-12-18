#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ xfs_fileoff_t ;
struct xfs_bmbt_irec {scalar_t__ br_startoff; scalar_t__ br_blockcount; scalar_t__ br_startblock; } ;

/* Variables and functions */
 scalar_t__ DELAYSTARTBLOCK ; 
 int /*<<< orphan*/  isnullstartblock (scalar_t__) ; 

__attribute__((used)) static bool
xfs_getbmap_next_rec(
	struct xfs_bmbt_irec	*rec,
	xfs_fileoff_t		total_end)
{
	xfs_fileoff_t		end = rec->br_startoff + rec->br_blockcount;

	if (end == total_end)
		return false;

	rec->br_startoff += rec->br_blockcount;
	if (!isnullstartblock(rec->br_startblock) &&
	    rec->br_startblock != DELAYSTARTBLOCK)
		rec->br_startblock += rec->br_blockcount;
	rec->br_blockcount = total_end - end;
	return true;
}