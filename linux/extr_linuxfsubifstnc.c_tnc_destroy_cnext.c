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
struct ubifs_znode {struct ubifs_znode* cnext; } ;
struct ubifs_info {scalar_t__ cmt_state; struct ubifs_znode* cnext; } ;

/* Variables and functions */
 scalar_t__ COMMIT_BROKEN ; 
 int /*<<< orphan*/  kfree (struct ubifs_znode*) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 scalar_t__ ubifs_zn_obsolete (struct ubifs_znode*) ; 

__attribute__((used)) static void tnc_destroy_cnext(struct ubifs_info *c)
{
	struct ubifs_znode *cnext;

	if (!c->cnext)
		return;
	ubifs_assert(c, c->cmt_state == COMMIT_BROKEN);
	cnext = c->cnext;
	do {
		struct ubifs_znode *znode = cnext;

		cnext = cnext->cnext;
		if (ubifs_zn_obsolete(znode))
			kfree(znode);
	} while (cnext && cnext != c->cnext);
}