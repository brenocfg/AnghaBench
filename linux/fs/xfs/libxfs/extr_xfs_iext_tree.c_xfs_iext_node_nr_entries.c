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
struct xfs_iext_node {scalar_t__* keys; } ;

/* Variables and functions */
 int KEYS_PER_NODE ; 
 scalar_t__ XFS_IEXT_KEY_INVALID ; 

__attribute__((used)) static int
xfs_iext_node_nr_entries(
	struct xfs_iext_node	*node,
	int			start)
{
	int			i;

	for (i = start; i < KEYS_PER_NODE; i++) {
		if (node->keys[i] == XFS_IEXT_KEY_INVALID)
			break;
	}

	return i;
}