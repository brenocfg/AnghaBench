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
typedef  size_t u8 ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;
struct cs43130_private {int /*<<< orphan*/ * hpload_dc; int /*<<< orphan*/  hpload_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct cs43130_private* i2c_get_clientdata (struct i2c_client*) ; 
 int scnprintf (char*,int /*<<< orphan*/ ,char*,...) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int cs43130_show_dc(struct device *dev, char *buf, u8 ch)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct cs43130_private *cs43130 = i2c_get_clientdata(client);

	if (!cs43130->hpload_done)
		return scnprintf(buf, PAGE_SIZE, "NO_HPLOAD\n");
	else
		return scnprintf(buf, PAGE_SIZE, "%u\n",
				 cs43130->hpload_dc[ch]);
}