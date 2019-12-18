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
typedef  int /*<<< orphan*/  xfs_fileoff_t ;
struct xfs_iext_node {int dummy; } ;

/* Variables and functions */
 int KEYS_PER_NODE ; 
 scalar_t__ xfs_iext_key_cmp (struct xfs_iext_node*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xfs_iext_node_insert_pos(
	struct xfs_iext_node	*node,
	xfs_fileoff_t		offset)
{
	int			i;

	for (i = 0; i < KEYS_PER_NODE; i++) {
		if (xfs_iext_key_cmp(node, i, offset) > 0)
			return i;
	}

	return KEYS_PER_NODE;
}