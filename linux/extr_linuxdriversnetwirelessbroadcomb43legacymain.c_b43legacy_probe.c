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
struct ssb_device_id {int dummy; } ;
struct ssb_device {int dummy; } ;
struct b43legacy_wl {int /*<<< orphan*/  firmware_load; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int b43legacy_one_core_attach (struct ssb_device*,struct b43legacy_wl*) ; 
 int /*<<< orphan*/  b43legacy_request_firmware ; 
 int /*<<< orphan*/  b43legacy_wireless_exit (struct ssb_device*,struct b43legacy_wl*) ; 
 int b43legacy_wireless_init (struct ssb_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct b43legacy_wl* ssb_get_devtypedata (struct ssb_device*) ; 

__attribute__((used)) static int b43legacy_probe(struct ssb_device *dev,
			 const struct ssb_device_id *id)
{
	struct b43legacy_wl *wl;
	int err;
	int first = 0;

	wl = ssb_get_devtypedata(dev);
	if (!wl) {
		/* Probing the first core - setup common struct b43legacy_wl */
		first = 1;
		err = b43legacy_wireless_init(dev);
		if (err)
			goto out;
		wl = ssb_get_devtypedata(dev);
		B43legacy_WARN_ON(!wl);
	}
	err = b43legacy_one_core_attach(dev, wl);
	if (err)
		goto err_wireless_exit;

	/* setup and start work to load firmware */
	INIT_WORK(&wl->firmware_load, b43legacy_request_firmware);
	schedule_work(&wl->firmware_load);

out:
	return err;

err_wireless_exit:
	if (first)
		b43legacy_wireless_exit(dev, wl);
	return err;
}