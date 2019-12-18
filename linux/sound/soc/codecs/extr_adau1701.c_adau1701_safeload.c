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
typedef  int uint8_t ;
struct sigmadsp {int /*<<< orphan*/  dev; } ;
struct i2c_client {int dummy; } ;
struct adau1701 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAU1701_DSPCTRL ; 
 unsigned int ADAU1701_DSPCTRL_IST ; 
 unsigned int ADAU1701_SAFELOAD_ADDR (unsigned int) ; 
 unsigned int ADAU1701_SAFELOAD_DATA (unsigned int) ; 
 int EIO ; 
 struct adau1701* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_master_send (struct i2c_client*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  put_unaligned_le16 (unsigned int,int*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adau1701_safeload(struct sigmadsp *sigmadsp, unsigned int addr,
	const uint8_t bytes[], size_t len)
{
	struct i2c_client *client = to_i2c_client(sigmadsp->dev);
	struct adau1701 *adau1701 = i2c_get_clientdata(client);
	unsigned int val;
	unsigned int i;
	uint8_t buf[10];
	int ret;

	ret = regmap_read(adau1701->regmap, ADAU1701_DSPCTRL, &val);
	if (ret)
		return ret;

	if (val & ADAU1701_DSPCTRL_IST)
		msleep(50);

	for (i = 0; i < len / 4; i++) {
		put_unaligned_le16(ADAU1701_SAFELOAD_DATA(i), buf);
		buf[2] = 0x00;
		memcpy(buf + 3, bytes + i * 4, 4);
		ret = i2c_master_send(client, buf, 7);
		if (ret < 0)
			return ret;
		else if (ret != 7)
			return -EIO;

		put_unaligned_le16(ADAU1701_SAFELOAD_ADDR(i), buf);
		put_unaligned_le16(addr + i, buf + 2);
		ret = i2c_master_send(client, buf, 4);
		if (ret < 0)
			return ret;
		else if (ret != 4)
			return -EIO;
	}

	return regmap_update_bits(adau1701->regmap, ADAU1701_DSPCTRL,
		ADAU1701_DSPCTRL_IST, ADAU1701_DSPCTRL_IST);
}