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
struct xfs_mount {int /*<<< orphan*/  m_attr_geo; int /*<<< orphan*/  m_dir_geo; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ) ; 

void
xfs_da_unmount(
	struct xfs_mount	*mp)
{
	kmem_free(mp->m_dir_geo);
	kmem_free(mp->m_attr_geo);
}