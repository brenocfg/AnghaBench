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
struct ubifs_info {int dummy; } ;
struct ubifs_idx_node {scalar_t__ branches; } ;
struct ubifs_branch {scalar_t__ key; } ;

/* Variables and functions */

__attribute__((used)) static inline void *ubifs_idx_key(const struct ubifs_info *c,
				  const struct ubifs_idx_node *idx)
{
	return (void *)((struct ubifs_branch *)idx->branches)->key;
}