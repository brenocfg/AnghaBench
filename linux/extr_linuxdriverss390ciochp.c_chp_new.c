#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct chp_id {size_t id; int /*<<< orphan*/  cssid; } ;
struct channel_subsystem {int /*<<< orphan*/  mutex; struct channel_path** chps; scalar_t__ cm_enabled; int /*<<< orphan*/  device; } ;
struct TYPE_7__ {int /*<<< orphan*/  release; int /*<<< orphan*/  groups; int /*<<< orphan*/ * parent; } ;
struct TYPE_6__ {int flags; } ;
struct channel_path {int state; TYPE_2__ dev; TYPE_1__ desc; int /*<<< orphan*/  lock; struct chp_id chpid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_MSG_EVENT (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t,int) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int chp_add_cmg_attr (struct channel_path*) ; 
 int /*<<< orphan*/  chp_attr_groups ; 
 scalar_t__ chp_is_registered (struct chp_id) ; 
 int /*<<< orphan*/  chp_release ; 
 int chp_update_desc (struct channel_path*) ; 
 struct channel_subsystem* css_by_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,int /*<<< orphan*/ ,size_t) ; 
 int device_register (TYPE_2__*) ; 
 int /*<<< orphan*/  device_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (struct channel_path*) ; 
 struct channel_path* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_2__*) ; 

int chp_new(struct chp_id chpid)
{
	struct channel_subsystem *css = css_by_id(chpid.cssid);
	struct channel_path *chp;
	int ret = 0;

	mutex_lock(&css->mutex);
	if (chp_is_registered(chpid))
		goto out;

	chp = kzalloc(sizeof(struct channel_path), GFP_KERNEL);
	if (!chp) {
		ret = -ENOMEM;
		goto out;
	}
	/* fill in status, etc. */
	chp->chpid = chpid;
	chp->state = 1;
	chp->dev.parent = &css->device;
	chp->dev.groups = chp_attr_groups;
	chp->dev.release = chp_release;
	mutex_init(&chp->lock);

	/* Obtain channel path description and fill it in. */
	ret = chp_update_desc(chp);
	if (ret)
		goto out_free;
	if ((chp->desc.flags & 0x80) == 0) {
		ret = -ENODEV;
		goto out_free;
	}
	dev_set_name(&chp->dev, "chp%x.%02x", chpid.cssid, chpid.id);

	/* make it known to the system */
	ret = device_register(&chp->dev);
	if (ret) {
		CIO_MSG_EVENT(0, "Could not register chp%x.%02x: %d\n",
			      chpid.cssid, chpid.id, ret);
		put_device(&chp->dev);
		goto out;
	}

	if (css->cm_enabled) {
		ret = chp_add_cmg_attr(chp);
		if (ret) {
			device_unregister(&chp->dev);
			goto out;
		}
	}
	css->chps[chpid.id] = chp;
	goto out;
out_free:
	kfree(chp);
out:
	mutex_unlock(&css->mutex);
	return ret;
}