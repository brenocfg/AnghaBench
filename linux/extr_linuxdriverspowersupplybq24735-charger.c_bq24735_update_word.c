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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int bq24735_read_word (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int bq24735_write_word (struct i2c_client*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int bq24735_update_word(struct i2c_client *client, u8 reg,
			       u16 mask, u16 value)
{
	unsigned int tmp;
	int ret;

	ret = bq24735_read_word(client, reg);
	if (ret < 0)
		return ret;

	tmp = ret & ~mask;
	tmp |= value & mask;

	return bq24735_write_word(client, reg, tmp);
}