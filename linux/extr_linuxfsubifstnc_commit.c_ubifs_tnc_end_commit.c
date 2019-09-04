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
struct TYPE_3__ {TYPE_2__* znode; } ;
struct ubifs_info {int /*<<< orphan*/  tnc_mutex; int /*<<< orphan*/ * ilebs; int /*<<< orphan*/ * cnext; TYPE_1__ zroot; } ;
struct TYPE_4__ {scalar_t__ level; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_cmt (char*,scalar_t__) ; 
 int /*<<< orphan*/  free_obsolete_znodes (struct ubifs_info*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int return_gap_lebs (struct ubifs_info*) ; 
 int write_index (struct ubifs_info*) ; 

int ubifs_tnc_end_commit(struct ubifs_info *c)
{
	int err;

	if (!c->cnext)
		return 0;

	err = return_gap_lebs(c);
	if (err)
		return err;

	err = write_index(c);
	if (err)
		return err;

	mutex_lock(&c->tnc_mutex);

	dbg_cmt("TNC height is %d", c->zroot.znode->level + 1);

	free_obsolete_znodes(c);

	c->cnext = NULL;
	kfree(c->ilebs);
	c->ilebs = NULL;

	mutex_unlock(&c->tnc_mutex);

	return 0;
}