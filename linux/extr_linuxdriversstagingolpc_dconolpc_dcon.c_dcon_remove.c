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
struct i2c_client {int dummy; } ;
struct dcon_priv {int /*<<< orphan*/  switch_source; int /*<<< orphan*/  bl_dev; int /*<<< orphan*/  reboot_nb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCON_IRQ ; 
 int /*<<< orphan*/  atomic_notifier_chain_unregister (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  backlight_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ dcon_device ; 
 int /*<<< orphan*/  dcon_panic_nb ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct dcon_priv*) ; 
 struct dcon_priv* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct dcon_priv*) ; 
 int /*<<< orphan*/  panic_notifier_list ; 
 int /*<<< orphan*/  platform_device_unregister (scalar_t__) ; 
 int /*<<< orphan*/  unregister_reboot_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dcon_remove(struct i2c_client *client)
{
	struct dcon_priv *dcon = i2c_get_clientdata(client);

	unregister_reboot_notifier(&dcon->reboot_nb);
	atomic_notifier_chain_unregister(&panic_notifier_list, &dcon_panic_nb);

	free_irq(DCON_IRQ, dcon);

	backlight_device_unregister(dcon->bl_dev);

	if (dcon_device)
		platform_device_unregister(dcon_device);
	cancel_work_sync(&dcon->switch_source);

	kfree(dcon);

	return 0;
}