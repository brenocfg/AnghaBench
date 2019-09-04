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
struct fusb302_chip {int /*<<< orphan*/  wq; int /*<<< orphan*/  tcpm_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fusb302_debugfs_exit (struct fusb302_chip*) ; 
 struct fusb302_chip* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcpm_unregister_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fusb302_remove(struct i2c_client *client)
{
	struct fusb302_chip *chip = i2c_get_clientdata(client);

	tcpm_unregister_port(chip->tcpm_port);
	destroy_workqueue(chip->wq);
	i2c_set_clientdata(client, NULL);
	fusb302_debugfs_exit(chip);

	return 0;
}