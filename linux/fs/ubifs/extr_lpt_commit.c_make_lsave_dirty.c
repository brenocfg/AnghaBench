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
struct ubifs_info {int lsave_lnum; int lsave_offs; int lpt_drty_flgs; int /*<<< orphan*/  lsave_sz; } ;

/* Variables and functions */
 int LSAVE_DIRTY ; 
 int /*<<< orphan*/  ubifs_add_lpt_dirt (struct ubifs_info*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int make_lsave_dirty(struct ubifs_info *c, int lnum, int offs)
{
	if (lnum != c->lsave_lnum || offs != c->lsave_offs)
		return 0; /* This lsave node is obsolete */
	if (!(c->lpt_drty_flgs & LSAVE_DIRTY)) {
		c->lpt_drty_flgs |= LSAVE_DIRTY;
		ubifs_add_lpt_dirt(c, c->lsave_lnum, c->lsave_sz);
	}
	return 0;
}