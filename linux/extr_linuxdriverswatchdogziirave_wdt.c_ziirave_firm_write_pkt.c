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

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  ZIIRAVE_CMD_DOWNLOAD_PACKET ; 
 scalar_t__ ZIIRAVE_FIRM_PKT_DATA_SIZE ; 
 int ZIIRAVE_FIRM_PKT_TOTAL_SIZE ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 
 int ziirave_firm_write_block_data (struct watchdog_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int ziirave_firm_write_pkt(struct watchdog_device *wdd,
				  const struct ihex_binrec *rec)
{
	struct i2c_client *client = to_i2c_client(wdd->parent);
	u8 i, checksum = 0, packet[ZIIRAVE_FIRM_PKT_TOTAL_SIZE];
	int ret;
	u16 addr;

	memset(packet, 0, ARRAY_SIZE(packet));

	/* Packet length */
	packet[0] = (u8)be16_to_cpu(rec->len);
	/* Packet address */
	addr = (be32_to_cpu(rec->addr) & 0xffff) >> 1;
	packet[1] = addr & 0xff;
	packet[2] = (addr & 0xff00) >> 8;

	/* Packet data */
	if (be16_to_cpu(rec->len) > ZIIRAVE_FIRM_PKT_DATA_SIZE)
		return -EMSGSIZE;
	memcpy(packet + 3, rec->data, be16_to_cpu(rec->len));

	/* Packet checksum */
	for (i = 0; i < ZIIRAVE_FIRM_PKT_TOTAL_SIZE - 1; i++)
		checksum += packet[i];
	packet[ZIIRAVE_FIRM_PKT_TOTAL_SIZE - 1] = checksum;

	ret = ziirave_firm_write_block_data(wdd, ZIIRAVE_CMD_DOWNLOAD_PACKET,
					    ARRAY_SIZE(packet), packet, true);
	if (ret)
		dev_err(&client->dev,
		      "Failed to write firmware packet at address 0x%04x: %d\n",
		      addr, ret);

	return ret;
}