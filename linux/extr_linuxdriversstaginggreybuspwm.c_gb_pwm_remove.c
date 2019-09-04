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
struct gbphy_device {int dummy; } ;
struct gb_pwm_chip {int /*<<< orphan*/  chip; struct gb_connection* connection; } ;
struct gb_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gb_connection_destroy (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_disable (struct gb_connection*) ; 
 struct gb_pwm_chip* gb_gbphy_get_data (struct gbphy_device*) ; 
 int /*<<< orphan*/  gbphy_runtime_get_noresume (struct gbphy_device*) ; 
 int gbphy_runtime_get_sync (struct gbphy_device*) ; 
 int /*<<< orphan*/  kfree (struct gb_pwm_chip*) ; 
 int /*<<< orphan*/  pwmchip_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gb_pwm_remove(struct gbphy_device *gbphy_dev)
{
	struct gb_pwm_chip *pwmc = gb_gbphy_get_data(gbphy_dev);
	struct gb_connection *connection = pwmc->connection;
	int ret;

	ret = gbphy_runtime_get_sync(gbphy_dev);
	if (ret)
		gbphy_runtime_get_noresume(gbphy_dev);

	pwmchip_remove(&pwmc->chip);
	gb_connection_disable(connection);
	gb_connection_destroy(connection);
	kfree(pwmc);
}