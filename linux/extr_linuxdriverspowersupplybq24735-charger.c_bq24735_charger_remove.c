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
struct bq24735 {int /*<<< orphan*/  poll; scalar_t__ poll_interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct bq24735* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static int bq24735_charger_remove(struct i2c_client *client)
{
	struct bq24735 *charger = i2c_get_clientdata(client);

	if (charger->poll_interval)
		cancel_delayed_work_sync(&charger->poll);

	return 0;
}