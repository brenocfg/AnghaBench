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
struct i2c_client {int addr; } ;
struct bq2415x_device {int chip; int /*<<< orphan*/  dev; } ;
typedef  enum bq2415x_chip { ____Placeholder_bq2415x_chip } bq2415x_chip ;

/* Variables and functions */
 int BQ24150 ; 
 int BQ24150A ; 
 int BQ24151 ; 
 int BQ24151A ; 
 int BQ24152 ; 
 int BQ24153 ; 
 int BQ24153A ; 
 int BQ24155 ; 
 int BQ24156 ; 
 int BQ24156A ; 
 int BQ24157S ; 
 int BQ24158 ; 
 int /*<<< orphan*/  BQ2415X_PART_NUMBER ; 
 int BQUNKNOWN ; 
 int bq2415x_exec_command (struct bq2415x_device*,int /*<<< orphan*/ ) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum bq2415x_chip bq2415x_detect_chip(struct bq2415x_device *bq)
{
	struct i2c_client *client = to_i2c_client(bq->dev);
	int ret = bq2415x_exec_command(bq, BQ2415X_PART_NUMBER);

	if (ret < 0)
		return ret;

	switch (client->addr) {
	case 0x6b:
		switch (ret) {
		case 0:
			if (bq->chip == BQ24151A)
				return bq->chip;
			return BQ24151;
		case 1:
			if (bq->chip == BQ24150A ||
				bq->chip == BQ24152 ||
				bq->chip == BQ24155)
				return bq->chip;
			return BQ24150;
		case 2:
			if (bq->chip == BQ24153A)
				return bq->chip;
			return BQ24153;
		default:
			return BQUNKNOWN;
		}
		break;

	case 0x6a:
		switch (ret) {
		case 0:
			if (bq->chip == BQ24156A)
				return bq->chip;
			return BQ24156;
		case 2:
			if (bq->chip == BQ24157S)
				return bq->chip;
			return BQ24158;
		default:
			return BQUNKNOWN;
		}
		break;
	}

	return BQUNKNOWN;
}