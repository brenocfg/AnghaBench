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
struct visorinput_devdata {int paused; unsigned int keycode_table_bytes; int /*<<< orphan*/  lock_visor_dev; scalar_t__ interrupts_enabled; int /*<<< orphan*/  visorinput_dev; int /*<<< orphan*/  keycode_table; struct visor_device* dev; } ;
struct TYPE_2__ {unsigned int x_res; unsigned int y_res; } ;
struct visor_input_channel_data {TYPE_1__ mouse; } ;
struct visor_device {int /*<<< orphan*/  device; } ;
struct channel_header {int dummy; } ;
typedef  enum visorinput_dev_type { ____Placeholder_visorinput_dev_type } visorinput_dev_type ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int KEYCODE_TABLE_BYTES ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct visorinput_devdata*) ; 
 int /*<<< orphan*/  input_free_device (int /*<<< orphan*/ ) ; 
 scalar_t__ input_register_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct visorinput_devdata*) ; 
 struct visorinput_devdata* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_client_keyboard (struct visorinput_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_client_mouse (struct visorinput_devdata*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  visorbus_enable_channel_interrupts (struct visor_device*) ; 
 unsigned int visorbus_read_channel (struct visor_device*,int,struct visor_input_channel_data*,unsigned int) ; 
#define  visorinput_keyboard 129 
#define  visorinput_mouse 128 
 int /*<<< orphan*/  visorkbd_ext_keycode ; 
 int /*<<< orphan*/  visorkbd_keycode ; 

__attribute__((used)) static struct visorinput_devdata *devdata_create(struct visor_device *dev,
						 enum visorinput_dev_type dtype)
{
	struct visorinput_devdata *devdata = NULL;
	unsigned int extra_bytes = 0;
	unsigned int size, xres, yres, err;
	struct visor_input_channel_data data;

	if (dtype == visorinput_keyboard)
		/* allocate room for devdata->keycode_table, filled in below */
		extra_bytes = KEYCODE_TABLE_BYTES * 2;
	devdata = kzalloc(sizeof(*devdata) + extra_bytes, GFP_KERNEL);
	if (!devdata)
		return NULL;
	mutex_init(&devdata->lock_visor_dev);
	mutex_lock(&devdata->lock_visor_dev);
	devdata->dev = dev;

	/*
	 * visorinput_open() can be called as soon as input_register_device()
	 * happens, and that will enable channel interrupts.  Setting paused
	 * prevents us from getting into visorinput_channel_interrupt() prior
	 * to the device structure being totally initialized.
	 */
	devdata->paused = true;

	/*
	 * This is an input device in a client guest partition, so we need to
	 * create whatever input nodes are necessary to deliver our inputs to
	 * the guest OS.
	 */
	switch (dtype) {
	case visorinput_keyboard:
		devdata->keycode_table_bytes = extra_bytes;
		memcpy(devdata->keycode_table, visorkbd_keycode,
		       KEYCODE_TABLE_BYTES);
		memcpy(devdata->keycode_table + KEYCODE_TABLE_BYTES,
		       visorkbd_ext_keycode, KEYCODE_TABLE_BYTES);
		devdata->visorinput_dev = setup_client_keyboard
			(devdata, devdata->keycode_table);
		if (!devdata->visorinput_dev)
			goto cleanups_register;
		break;
	case visorinput_mouse:
		size = sizeof(struct visor_input_channel_data);
		err = visorbus_read_channel(dev, sizeof(struct channel_header),
					    &data, size);
		if (err)
			goto cleanups_register;
		xres = data.mouse.x_res;
		yres = data.mouse.y_res;
		devdata->visorinput_dev = setup_client_mouse(devdata, xres,
							     yres);
		if (!devdata->visorinput_dev)
			goto cleanups_register;
		break;
	default:
		/* No other input devices supported */
		break;
	}

	dev_set_drvdata(&dev->device, devdata);
	mutex_unlock(&devdata->lock_visor_dev);

	/*
	 * Device struct is completely set up now, with the exception of
	 * visorinput_dev being registered. We need to unlock before we
	 * register the device, because this can cause an on-stack call of
	 * visorinput_open(), which would deadlock if we had the lock.
	 */
	if (input_register_device(devdata->visorinput_dev)) {
		input_free_device(devdata->visorinput_dev);
		goto err_kfree_devdata;
	}

	mutex_lock(&devdata->lock_visor_dev);
	/*
	 * Establish calls to visorinput_channel_interrupt() if that is the
	 * desired state that we've kept track of in interrupts_enabled while
	 * the device was being created.
	 */
	devdata->paused = false;
	if (devdata->interrupts_enabled)
		visorbus_enable_channel_interrupts(dev);
	mutex_unlock(&devdata->lock_visor_dev);

	return devdata;

cleanups_register:
	mutex_unlock(&devdata->lock_visor_dev);
err_kfree_devdata:
	kfree(devdata);
	return NULL;
}