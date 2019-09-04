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
typedef  scalar_t__ u8 ;
struct pi3usb30532 {scalar_t__ conf; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PI3USB30532_CONF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_smbus_write_byte_data (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int pi3usb30532_set_conf(struct pi3usb30532 *pi, u8 new_conf)
{
	int ret = 0;

	if (pi->conf == new_conf)
		return 0;

	ret = i2c_smbus_write_byte_data(pi->client, PI3USB30532_CONF, new_conf);
	if (ret) {
		dev_err(&pi->client->dev, "Error writing conf: %d\n", ret);
		return ret;
	}

	pi->conf = new_conf;
	return 0;
}