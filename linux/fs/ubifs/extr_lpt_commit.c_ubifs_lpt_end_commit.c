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
struct ubifs_info {int /*<<< orphan*/  lp_mutex; int /*<<< orphan*/  lpt_cnext; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_lp (char*) ; 
 int /*<<< orphan*/  free_obsolete_cnodes (struct ubifs_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int write_cnodes (struct ubifs_info*) ; 

int ubifs_lpt_end_commit(struct ubifs_info *c)
{
	int err;

	dbg_lp("");

	if (!c->lpt_cnext)
		return 0;

	err = write_cnodes(c);
	if (err)
		return err;

	mutex_lock(&c->lp_mutex);
	free_obsolete_cnodes(c);
	mutex_unlock(&c->lp_mutex);

	return 0;
}