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
struct ubifs_info {struct ubifs_cnode* lpt_cnext; } ;
struct ubifs_cnode {struct ubifs_cnode* cnext; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBSOLETE_CNODE ; 
 int /*<<< orphan*/  kfree (struct ubifs_cnode*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_obsolete_cnodes(struct ubifs_info *c)
{
	struct ubifs_cnode *cnode, *cnext;

	cnext = c->lpt_cnext;
	if (!cnext)
		return;
	do {
		cnode = cnext;
		cnext = cnode->cnext;
		if (test_bit(OBSOLETE_CNODE, &cnode->flags))
			kfree(cnode);
		else
			cnode->cnext = NULL;
	} while (cnext != c->lpt_cnext);
	c->lpt_cnext = NULL;
}