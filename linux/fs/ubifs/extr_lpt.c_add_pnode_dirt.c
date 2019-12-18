#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ubifs_pnode {size_t iip; TYPE_2__* parent; } ;
struct ubifs_info {int /*<<< orphan*/  pnode_sz; } ;
struct TYPE_4__ {TYPE_1__* nbranch; } ;
struct TYPE_3__ {int /*<<< orphan*/  lnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  ubifs_add_lpt_dirt (struct ubifs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_pnode_dirt(struct ubifs_info *c, struct ubifs_pnode *pnode)
{
	ubifs_add_lpt_dirt(c, pnode->parent->nbranch[pnode->iip].lnum,
			   c->pnode_sz);
}