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
struct TYPE_3__ {int /*<<< orphan*/  m_filestream; } ;
typedef  TYPE_1__ xfs_mount_t ;

/* Variables and functions */
 int /*<<< orphan*/  xfs_mru_cache_destroy (int /*<<< orphan*/ ) ; 

void
xfs_filestream_unmount(
	xfs_mount_t	*mp)
{
	xfs_mru_cache_destroy(mp->m_filestream);
}