#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  set; struct device* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  set; struct device* dev; } ;
struct pi3usb30532 {int conf; TYPE_1__ sw; TYPE_3__ mux; int /*<<< orphan*/  lock; struct i2c_client* client; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PI3USB30532_CONF ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct pi3usb30532* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct pi3usb30532*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pi3usb30532_mux_set ; 
 int /*<<< orphan*/  pi3usb30532_sw_set ; 
 int typec_mux_register (TYPE_3__*) ; 
 int typec_switch_register (TYPE_1__*) ; 
 int /*<<< orphan*/  typec_switch_unregister (TYPE_1__*) ; 

__attribute__((used)) static int pi3usb30532_probe(struct i2c_client *client)
{
	struct device *dev = &client->dev;
	struct pi3usb30532 *pi;
	int ret;

	pi = devm_kzalloc(dev, sizeof(*pi), GFP_KERNEL);
	if (!pi)
		return -ENOMEM;

	pi->client = client;
	pi->sw.dev = dev;
	pi->sw.set = pi3usb30532_sw_set;
	pi->mux.dev = dev;
	pi->mux.set = pi3usb30532_mux_set;
	mutex_init(&pi->lock);

	ret = i2c_smbus_read_byte_data(client, PI3USB30532_CONF);
	if (ret < 0) {
		dev_err(dev, "Error reading config register %d\n", ret);
		return ret;
	}
	pi->conf = ret;

	ret = typec_switch_register(&pi->sw);
	if (ret) {
		dev_err(dev, "Error registering typec switch: %d\n", ret);
		return ret;
	}

	ret = typec_mux_register(&pi->mux);
	if (ret) {
		typec_switch_unregister(&pi->sw);
		dev_err(dev, "Error registering typec mux: %d\n", ret);
		return ret;
	}

	i2c_set_clientdata(client, pi);
	return 0;
}