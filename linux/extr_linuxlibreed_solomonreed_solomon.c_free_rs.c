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
struct rs_control {struct rs_control* genpoly; struct rs_control* index_of; struct rs_control* alpha_to; int /*<<< orphan*/  list; int /*<<< orphan*/  users; struct rs_control* codec; } ;
struct rs_codec {struct rs_codec* genpoly; struct rs_codec* index_of; struct rs_codec* alpha_to; int /*<<< orphan*/  list; int /*<<< orphan*/  users; struct rs_codec* codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct rs_control*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rslistlock ; 

void free_rs(struct rs_control *rs)
{
	struct rs_codec *cd;

	if (!rs)
		return;

	cd = rs->codec;
	mutex_lock(&rslistlock);
	cd->users--;
	if(!cd->users) {
		list_del(&cd->list);
		kfree(cd->alpha_to);
		kfree(cd->index_of);
		kfree(cd->genpoly);
		kfree(cd);
	}
	mutex_unlock(&rslistlock);
	kfree(rs);
}