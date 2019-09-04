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
struct ulist_node {scalar_t__ aux; } ;
struct btrfs_qgroup {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct btrfs_qgroup* unode_aux_to_qgroup(struct ulist_node *n)
{
	return (struct btrfs_qgroup *)(uintptr_t)n->aux;
}