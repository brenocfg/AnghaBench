#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xfs_rtblock_t ;
struct TYPE_2__ {scalar_t__ sb_rblocks; } ;
struct xfs_mount {TYPE_1__ m_sb; } ;

/* Variables and functions */

bool
xfs_verify_rtbno(
	struct xfs_mount	*mp,
	xfs_rtblock_t		rtbno)
{
	return rtbno < mp->m_sb.sb_rblocks;
}