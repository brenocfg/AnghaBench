#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {TYPE_1__* private_data; } ;
typedef  int /*<<< orphan*/  VCHIQ_STATE_T ;
typedef  TYPE_1__* VCHIQ_INSTANCE_T ;
struct TYPE_6__ {int /*<<< orphan*/  tgid; } ;
struct TYPE_5__ {int /*<<< orphan*/  bulk_waiter_list; int /*<<< orphan*/  bulk_waiter_list_mutex; int /*<<< orphan*/  completion_mutex; int /*<<< orphan*/  remove_event; int /*<<< orphan*/  insert_event; int /*<<< orphan*/  pid; int /*<<< orphan*/ * state; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOTCONN ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
#define  VCHIQ_MINOR 128 
 TYPE_4__* current ; 
 int iminor (struct inode*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_arm_log_level ; 
 int /*<<< orphan*/  vchiq_debugfs_add_instance (TYPE_1__*) ; 
 int /*<<< orphan*/ * vchiq_get_state () ; 
 int /*<<< orphan*/  vchiq_log_error (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  vchiq_log_info (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
vchiq_open(struct inode *inode, struct file *file)
{
	int dev = iminor(inode) & 0x0f;

	vchiq_log_info(vchiq_arm_log_level, "vchiq_open");
	switch (dev) {
	case VCHIQ_MINOR: {
		VCHIQ_STATE_T *state = vchiq_get_state();
		VCHIQ_INSTANCE_T instance;

		if (!state) {
			vchiq_log_error(vchiq_arm_log_level,
				"vchiq has no connection to VideoCore");
			return -ENOTCONN;
		}

		instance = kzalloc(sizeof(*instance), GFP_KERNEL);
		if (!instance)
			return -ENOMEM;

		instance->state = state;
		instance->pid = current->tgid;

		vchiq_debugfs_add_instance(instance);

		sema_init(&instance->insert_event, 0);
		sema_init(&instance->remove_event, 0);
		mutex_init(&instance->completion_mutex);
		mutex_init(&instance->bulk_waiter_list_mutex);
		INIT_LIST_HEAD(&instance->bulk_waiter_list);

		file->private_data = instance;
	} break;

	default:
		vchiq_log_error(vchiq_arm_log_level,
			"Unknown minor device: %d", dev);
		return -ENXIO;
	}

	return 0;
}