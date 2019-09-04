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
struct smbios_device {int /*<<< orphan*/  list; void* call_fn; struct device* device; } ;
struct device {TYPE_1__* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct smbios_device* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smbios_device_list ; 
 int /*<<< orphan*/  smbios_mutex ; 

int dell_smbios_register_device(struct device *d, void *call_fn)
{
	struct smbios_device *priv;

	priv = devm_kzalloc(d, sizeof(struct smbios_device), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;
	get_device(d);
	priv->device = d;
	priv->call_fn = call_fn;
	mutex_lock(&smbios_mutex);
	list_add_tail(&priv->list, &smbios_device_list);
	mutex_unlock(&smbios_mutex);
	dev_dbg(d, "Added device: %s\n", d->driver->name);
	return 0;
}