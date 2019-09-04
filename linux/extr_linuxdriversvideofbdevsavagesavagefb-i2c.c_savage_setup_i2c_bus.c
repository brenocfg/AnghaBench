#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_11__ {TYPE_1__ dev; TYPE_2__* algo_data; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int udelay; int timeout; int /*<<< orphan*/  (* setscl ) (struct savagefb_i2c_chan*,int) ;int /*<<< orphan*/  (* setsda ) (struct savagefb_i2c_chan*,int) ;struct savagefb_i2c_chan* data; } ;
struct savagefb_i2c_chan {TYPE_4__* par; TYPE_5__ adapter; TYPE_2__ algo; } ;
struct TYPE_10__ {TYPE_3__* pcidev; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,char const*) ; 
 int i2c_bit_add_bus (TYPE_5__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_5__*,struct savagefb_i2c_chan*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  stub1 (struct savagefb_i2c_chan*,int) ; 
 int /*<<< orphan*/  stub2 (struct savagefb_i2c_chan*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int savage_setup_i2c_bus(struct savagefb_i2c_chan *chan,
				const char *name)
{
	int rc = 0;

	if (chan->par) {
		strcpy(chan->adapter.name, name);
		chan->adapter.owner		= THIS_MODULE;
		chan->adapter.algo_data		= &chan->algo;
		chan->adapter.dev.parent	= &chan->par->pcidev->dev;
		chan->algo.udelay		= 10;
		chan->algo.timeout		= 20;
		chan->algo.data 		= chan;

		i2c_set_adapdata(&chan->adapter, chan);

		/* Raise SCL and SDA */
		chan->algo.setsda(chan, 1);
		chan->algo.setscl(chan, 1);
		udelay(20);

		rc = i2c_bit_add_bus(&chan->adapter);

		if (rc == 0)
			dev_dbg(&chan->par->pcidev->dev,
				"I2C bus %s registered.\n", name);
		else
			dev_warn(&chan->par->pcidev->dev,
				 "Failed to register I2C bus %s.\n", name);
	}

	return rc;
}