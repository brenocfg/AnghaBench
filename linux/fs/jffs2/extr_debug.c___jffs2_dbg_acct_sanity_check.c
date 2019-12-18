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
struct jffs2_sb_info {int /*<<< orphan*/  erase_completion_lock; } ;
struct jffs2_eraseblock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  jffs2_dbg_acct_sanity_check_nolock (struct jffs2_sb_info*,struct jffs2_eraseblock*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void
__jffs2_dbg_acct_sanity_check(struct jffs2_sb_info *c,
			      struct jffs2_eraseblock *jeb)
{
	spin_lock(&c->erase_completion_lock);
	jffs2_dbg_acct_sanity_check_nolock(c, jeb);
	spin_unlock(&c->erase_completion_lock);
}