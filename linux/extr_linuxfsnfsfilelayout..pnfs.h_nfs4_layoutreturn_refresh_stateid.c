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
struct pnfs_layout_range {int dummy; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;

/* Variables and functions */

__attribute__((used)) static inline bool nfs4_layoutreturn_refresh_stateid(nfs4_stateid *dst,
		struct pnfs_layout_range *dst_range,
		struct inode *inode)
{
	return false;
}