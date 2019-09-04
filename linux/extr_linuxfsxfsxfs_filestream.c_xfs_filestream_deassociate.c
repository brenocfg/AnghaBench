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
struct xfs_inode {int /*<<< orphan*/  i_ino; TYPE_1__* i_mount; } ;
struct TYPE_2__ {int /*<<< orphan*/  m_filestream; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfs_mru_cache_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
xfs_filestream_deassociate(
	struct xfs_inode	*ip)
{
	xfs_mru_cache_delete(ip->i_mount->m_filestream, ip->i_ino);
}