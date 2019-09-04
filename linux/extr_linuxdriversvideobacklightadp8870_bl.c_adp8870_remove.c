#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct i2c_client {int dummy; } ;
struct adp8870_bl {TYPE_3__* bl; TYPE_1__* pdata; scalar_t__ led; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_6__ {TYPE_2__ dev; } ;
struct TYPE_4__ {scalar_t__ en_ambl_sens; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADP8870_MDCR ; 
 int /*<<< orphan*/  NSTBY ; 
 int /*<<< orphan*/  adp8870_bl_attr_group ; 
 int /*<<< orphan*/  adp8870_clr_bits (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adp8870_led_remove (struct i2c_client*) ; 
 struct adp8870_bl* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adp8870_remove(struct i2c_client *client)
{
	struct adp8870_bl *data = i2c_get_clientdata(client);

	adp8870_clr_bits(client, ADP8870_MDCR, NSTBY);

	if (data->led)
		adp8870_led_remove(client);

	if (data->pdata->en_ambl_sens)
		sysfs_remove_group(&data->bl->dev.kobj,
			&adp8870_bl_attr_group);

	return 0;
}