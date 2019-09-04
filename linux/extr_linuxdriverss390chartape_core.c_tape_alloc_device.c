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
struct tape_device {int first_minor; int /*<<< orphan*/  tape_dnr; int /*<<< orphan*/  ref_count; scalar_t__* modeset_byte; int /*<<< orphan*/  medium_state; int /*<<< orphan*/  tape_state; int /*<<< orphan*/  wait_queue; int /*<<< orphan*/  state_change_wq; int /*<<< orphan*/  node; int /*<<< orphan*/  req_queue; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_EXCEPTION (int,char*) ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct tape_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MS_UNKNOWN ; 
 int /*<<< orphan*/  TS_INIT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tape_device*) ; 
 scalar_t__* kmalloc (int,int) ; 
 struct tape_device* kzalloc (int,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tape_delayed_next_request ; 

__attribute__((used)) static struct tape_device *
tape_alloc_device(void)
{
	struct tape_device *device;

	device = kzalloc(sizeof(struct tape_device), GFP_KERNEL);
	if (device == NULL) {
		DBF_EXCEPTION(2, "ti:no mem\n");
		return ERR_PTR(-ENOMEM);
	}
	device->modeset_byte = kmalloc(1, GFP_KERNEL | GFP_DMA);
	if (device->modeset_byte == NULL) {
		DBF_EXCEPTION(2, "ti:no mem\n");
		kfree(device);
		return ERR_PTR(-ENOMEM);
	}
	mutex_init(&device->mutex);
	INIT_LIST_HEAD(&device->req_queue);
	INIT_LIST_HEAD(&device->node);
	init_waitqueue_head(&device->state_change_wq);
	init_waitqueue_head(&device->wait_queue);
	device->tape_state = TS_INIT;
	device->medium_state = MS_UNKNOWN;
	*device->modeset_byte = 0;
	device->first_minor = -1;
	atomic_set(&device->ref_count, 1);
	INIT_DELAYED_WORK(&device->tape_dnr, tape_delayed_next_request);

	return device;
}