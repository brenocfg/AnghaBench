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
struct node_info {int /*<<< orphan*/  version; int /*<<< orphan*/  blk_addr; int /*<<< orphan*/  ino; int /*<<< orphan*/  nid; } ;

/* Variables and functions */

__attribute__((used)) static inline void copy_node_info(struct node_info *dst,
						struct node_info *src)
{
	dst->nid = src->nid;
	dst->ino = src->ino;
	dst->blk_addr = src->blk_addr;
	dst->version = src->version;
	/* should not copy flag here */
}