#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mdev_state {int nr_ports; int irq_index; int /*<<< orphan*/  next; struct mdev_device* mdev; int /*<<< orphan*/  ops_lock; int /*<<< orphan*/ * vconfig; int /*<<< orphan*/  rxtx_lock; TYPE_1__* s; } ;
struct mdev_device {int dummy; } ;
struct kobject {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {void* max_fifo_size; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* MAX_FIFO_SIZE ; 
 int MTTY_CONFIG_SPACE_SIZE ; 
 int MTTY_STRING_LEN ; 
 char* dev_driver_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mdev_state*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdev_devices_list ; 
 int /*<<< orphan*/  mdev_list_lock ; 
 int /*<<< orphan*/  mdev_parent_dev (struct mdev_device*) ; 
 int /*<<< orphan*/  mdev_set_drvdata (struct mdev_device*,struct mdev_state*) ; 
 int /*<<< orphan*/  mtty_create_config_space (struct mdev_state*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mtty_create(struct kobject *kobj, struct mdev_device *mdev)
{
	struct mdev_state *mdev_state;
	char name[MTTY_STRING_LEN];
	int nr_ports = 0, i;

	if (!mdev)
		return -EINVAL;

	for (i = 0; i < 2; i++) {
		snprintf(name, MTTY_STRING_LEN, "%s-%d",
			dev_driver_string(mdev_parent_dev(mdev)), i + 1);
		if (!strcmp(kobj->name, name)) {
			nr_ports = i + 1;
			break;
		}
	}

	if (!nr_ports)
		return -EINVAL;

	mdev_state = kzalloc(sizeof(struct mdev_state), GFP_KERNEL);
	if (mdev_state == NULL)
		return -ENOMEM;

	mdev_state->nr_ports = nr_ports;
	mdev_state->irq_index = -1;
	mdev_state->s[0].max_fifo_size = MAX_FIFO_SIZE;
	mdev_state->s[1].max_fifo_size = MAX_FIFO_SIZE;
	mutex_init(&mdev_state->rxtx_lock);
	mdev_state->vconfig = kzalloc(MTTY_CONFIG_SPACE_SIZE, GFP_KERNEL);

	if (mdev_state->vconfig == NULL) {
		kfree(mdev_state);
		return -ENOMEM;
	}

	mutex_init(&mdev_state->ops_lock);
	mdev_state->mdev = mdev;
	mdev_set_drvdata(mdev, mdev_state);

	mtty_create_config_space(mdev_state);

	mutex_lock(&mdev_list_lock);
	list_add(&mdev_state->next, &mdev_devices_list);
	mutex_unlock(&mdev_list_lock);

	return 0;
}