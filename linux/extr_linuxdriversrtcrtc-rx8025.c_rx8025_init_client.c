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
typedef  int u8 ;
struct rx8025_data {int ctrl1; int /*<<< orphan*/  client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int RX8025_BIT_CTRL1_TEST ; 
 int RX8025_BIT_CTRL2_CTFG ; 
 int RX8025_BIT_CTRL2_DAFG ; 
 int RX8025_BIT_CTRL2_WAFG ; 
 int /*<<< orphan*/  RX8025_REG_CTRL1 ; 
 int /*<<< orphan*/  RX8025_REG_CTRL2 ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct rx8025_data* i2c_get_clientdata (struct i2c_client*) ; 
 int rx8025_read_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int rx8025_write_reg (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rx8025_init_client(struct i2c_client *client)
{
	struct rx8025_data *rx8025 = i2c_get_clientdata(client);
	u8 ctrl[2], ctrl2;
	int need_clear = 0;
	int err;

	err = rx8025_read_regs(rx8025->client, RX8025_REG_CTRL1, 2, ctrl);
	if (err)
		goto out;

	/* Keep test bit zero ! */
	rx8025->ctrl1 = ctrl[0] & ~RX8025_BIT_CTRL1_TEST;

	if (ctrl[1] & (RX8025_BIT_CTRL2_DAFG | RX8025_BIT_CTRL2_WAFG)) {
		dev_warn(&client->dev, "Alarm was detected\n");
		need_clear = 1;
	}

	if (ctrl[1] & RX8025_BIT_CTRL2_CTFG)
		need_clear = 1;

	if (need_clear) {
		ctrl2 = ctrl[1];
		ctrl2 &= ~(RX8025_BIT_CTRL2_CTFG | RX8025_BIT_CTRL2_WAFG |
			   RX8025_BIT_CTRL2_DAFG);

		err = rx8025_write_reg(client, RX8025_REG_CTRL2, ctrl2);
	}
out:
	return err;
}