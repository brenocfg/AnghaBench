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
struct greybus_descriptor_cport {scalar_t__ protocol_id; int /*<<< orphan*/  id; } ;
struct greybus_bundle_id {int dummy; } ;
struct gb_vibrator_device {int minor; int /*<<< orphan*/  delayed_work; struct gb_connection* dev; struct gb_connection* connection; } ;
struct gb_connection {int dummy; } ;
struct gb_bundle {int num_cports; int /*<<< orphan*/  dev; struct greybus_descriptor_cport* cport_desc; } ;
typedef  struct gb_connection device ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ GREYBUS_PROTOCOL_VIBRATOR ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct gb_connection*) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct gb_connection*) ; 
 struct gb_connection* device_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct gb_vibrator_device*,char*,int) ; 
 struct gb_connection* gb_connection_create (struct gb_bundle*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gb_connection_destroy (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_disable (struct gb_connection*) ; 
 int gb_connection_enable (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_set_data (struct gb_connection*,struct gb_vibrator_device*) ; 
 int /*<<< orphan*/  gb_pm_runtime_put_autosuspend (struct gb_bundle*) ; 
 int /*<<< orphan*/  gb_vibrator_worker ; 
 int /*<<< orphan*/  greybus_set_drvdata (struct gb_bundle*,struct gb_vibrator_device*) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct gb_vibrator_device*) ; 
 struct gb_vibrator_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  minors ; 
 int /*<<< orphan*/  vibrator_class ; 

__attribute__((used)) static int gb_vibrator_probe(struct gb_bundle *bundle,
			     const struct greybus_bundle_id *id)
{
	struct greybus_descriptor_cport *cport_desc;
	struct gb_connection *connection;
	struct gb_vibrator_device *vib;
	struct device *dev;
	int retval;

	if (bundle->num_cports != 1)
		return -ENODEV;

	cport_desc = &bundle->cport_desc[0];
	if (cport_desc->protocol_id != GREYBUS_PROTOCOL_VIBRATOR)
		return -ENODEV;

	vib = kzalloc(sizeof(*vib), GFP_KERNEL);
	if (!vib)
		return -ENOMEM;

	connection = gb_connection_create(bundle, le16_to_cpu(cport_desc->id),
					  NULL);
	if (IS_ERR(connection)) {
		retval = PTR_ERR(connection);
		goto err_free_vib;
	}
	gb_connection_set_data(connection, vib);

	vib->connection = connection;

	greybus_set_drvdata(bundle, vib);

	retval = gb_connection_enable(connection);
	if (retval)
		goto err_connection_destroy;

	/*
	 * For now we create a device in sysfs for the vibrator, but odds are
	 * there is a "real" device somewhere in the kernel for this, but I
	 * can't find it at the moment...
	 */
	vib->minor = ida_simple_get(&minors, 0, 0, GFP_KERNEL);
	if (vib->minor < 0) {
		retval = vib->minor;
		goto err_connection_disable;
	}
	dev = device_create(&vibrator_class, &bundle->dev,
			    MKDEV(0, 0), vib, "vibrator%d", vib->minor);
	if (IS_ERR(dev)) {
		retval = -EINVAL;
		goto err_ida_remove;
	}
	vib->dev = dev;

	INIT_DELAYED_WORK(&vib->delayed_work, gb_vibrator_worker);

	gb_pm_runtime_put_autosuspend(bundle);

	return 0;

err_ida_remove:
	ida_simple_remove(&minors, vib->minor);
err_connection_disable:
	gb_connection_disable(connection);
err_connection_destroy:
	gb_connection_destroy(connection);
err_free_vib:
	kfree(vib);

	return retval;
}