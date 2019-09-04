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
struct xfs_iext_node {scalar_t__* keys; } ;

/* Variables and functions */

__attribute__((used)) static inline int
xfs_iext_key_cmp(
	struct xfs_iext_node	*node,
	int			n,
	xfs_fileoff_t		offset)
{
	if (node->keys[n] > offset)
		return 1;
	if (node->keys[n] < offset)
		return -1;
	return 0;
}