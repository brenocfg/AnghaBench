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
struct team_mode_item {int /*<<< orphan*/  list; struct team_mode const* mode; } ;
struct team_mode {scalar_t__ priv_size; int /*<<< orphan*/  kind; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ TEAM_MODE_PRIV_SIZE ; 
 scalar_t__ __find_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_good_mode_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct team_mode_item*) ; 
 struct team_mode_item* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mode_list ; 
 int /*<<< orphan*/  mode_list_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int team_mode_register(const struct team_mode *mode)
{
	int err = 0;
	struct team_mode_item *mitem;

	if (!is_good_mode_name(mode->kind) ||
	    mode->priv_size > TEAM_MODE_PRIV_SIZE)
		return -EINVAL;

	mitem = kmalloc(sizeof(*mitem), GFP_KERNEL);
	if (!mitem)
		return -ENOMEM;

	spin_lock(&mode_list_lock);
	if (__find_mode(mode->kind)) {
		err = -EEXIST;
		kfree(mitem);
		goto unlock;
	}
	mitem->mode = mode;
	list_add_tail(&mitem->list, &mode_list);
unlock:
	spin_unlock(&mode_list_lock);
	return err;
}