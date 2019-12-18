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
struct xfs_inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfs_inode_measure_sickness (struct xfs_inode*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static inline bool
xfs_inode_has_sickness(struct xfs_inode *ip, unsigned int mask)
{
	unsigned int	sick, checked;

	xfs_inode_measure_sickness(ip, &sick, &checked);
	return sick & mask;
}