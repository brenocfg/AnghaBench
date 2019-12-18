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
struct ubifs_info {scalar_t__ cmt_state; int /*<<< orphan*/  cs_lock; } ;

/* Variables and functions */
 scalar_t__ COMMIT_BACKGROUND ; 
 scalar_t__ COMMIT_REQUIRED ; 
 int /*<<< orphan*/  dbg_cmt (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int ubifs_gc_should_commit(struct ubifs_info *c)
{
	int ret = 0;

	spin_lock(&c->cs_lock);
	if (c->cmt_state == COMMIT_BACKGROUND) {
		dbg_cmt("commit required now");
		c->cmt_state = COMMIT_REQUIRED;
	} else
		dbg_cmt("commit not requested");
	if (c->cmt_state == COMMIT_REQUIRED)
		ret = 1;
	spin_unlock(&c->cs_lock);
	return ret;
}