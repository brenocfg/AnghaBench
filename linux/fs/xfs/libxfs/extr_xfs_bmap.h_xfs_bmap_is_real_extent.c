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
struct xfs_bmbt_irec {scalar_t__ br_state; scalar_t__ br_startblock; } ;

/* Variables and functions */
 scalar_t__ DELAYSTARTBLOCK ; 
 scalar_t__ HOLESTARTBLOCK ; 
 scalar_t__ XFS_EXT_UNWRITTEN ; 
 int /*<<< orphan*/  isnullstartblock (scalar_t__) ; 

__attribute__((used)) static inline bool xfs_bmap_is_real_extent(struct xfs_bmbt_irec *irec)
{
	return irec->br_state != XFS_EXT_UNWRITTEN &&
		irec->br_startblock != HOLESTARTBLOCK &&
		irec->br_startblock != DELAYSTARTBLOCK &&
		!isnullstartblock(irec->br_startblock);
}