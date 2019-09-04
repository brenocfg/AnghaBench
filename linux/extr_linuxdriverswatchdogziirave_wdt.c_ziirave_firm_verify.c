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
typedef  int u16 ;
struct watchdog_device {int /*<<< orphan*/  parent; } ;
struct ihex_binrec {int /*<<< orphan*/  len; int /*<<< orphan*/  data; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct firmware {scalar_t__ data; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ZIIRAVE_CMD_DOWNLOAD_READ_BYTE ; 
 int ZIIRAVE_FIRM_FLASH_MEMORY_END ; 
 int ZIIRAVE_FIRM_FLASH_MEMORY_START ; 
 int ZIIRAVE_FIRM_PKT_DATA_SIZE ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct ihex_binrec* ihex_next_binrec (struct ihex_binrec const*) ; 
 scalar_t__ memcmp (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 
 int ziirave_firm_set_read_addr (struct watchdog_device*,int) ; 

__attribute__((used)) static int ziirave_firm_verify(struct watchdog_device *wdd,
			       const struct firmware *fw)
{
	struct i2c_client *client = to_i2c_client(wdd->parent);
	const struct ihex_binrec *rec;
	int i, ret;
	u8 data[ZIIRAVE_FIRM_PKT_DATA_SIZE];
	u16 addr;

	for (rec = (void *)fw->data; rec; rec = ihex_next_binrec(rec)) {
		/* Zero length marks end of records */
		if (!be16_to_cpu(rec->len))
			break;

		addr = (be32_to_cpu(rec->addr) & 0xffff) >> 1;
		if (addr < ZIIRAVE_FIRM_FLASH_MEMORY_START ||
		    addr > ZIIRAVE_FIRM_FLASH_MEMORY_END)
			continue;

		ret = ziirave_firm_set_read_addr(wdd, addr);
		if (ret) {
			dev_err(&client->dev,
				"Failed to send SET_READ_ADDR command: %d\n",
				ret);
			return ret;
		}

		for (i = 0; i < ARRAY_SIZE(data); i++) {
			ret = i2c_smbus_read_byte_data(client,
						ZIIRAVE_CMD_DOWNLOAD_READ_BYTE);
			if (ret < 0) {
				dev_err(&client->dev,
					"Failed to READ DATA: %d\n", ret);
				return ret;
			}
			data[i] = ret;
		}

		if (memcmp(data, rec->data, be16_to_cpu(rec->len))) {
			dev_err(&client->dev,
				"Firmware mismatch at address 0x%04x\n", addr);
			return -EINVAL;
		}
	}

	return 0;
}