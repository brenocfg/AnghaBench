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
typedef  int /*<<< orphan*/  u16 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX17040_VER ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max17040_read_reg (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void max17040_get_version(struct i2c_client *client)
{
	u16 version;

	version = max17040_read_reg(client, MAX17040_VER);

	dev_info(&client->dev, "MAX17040 Fuel-Gauge Ver 0x%x\n", version);
}