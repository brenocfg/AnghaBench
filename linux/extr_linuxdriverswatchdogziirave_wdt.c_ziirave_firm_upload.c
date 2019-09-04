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
struct watchdog_device {int /*<<< orphan*/  parent; } ;
typedef  struct ihex_binrec {void* len; scalar_t__ data; int /*<<< orphan*/  addr; } const ihex_binrec ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct firmware {scalar_t__ data; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ZIIRAVE_CMD_DOWNLOAD_END ; 
 int /*<<< orphan*/  ZIIRAVE_CMD_DOWNLOAD_START ; 
 int /*<<< orphan*/  ZIIRAVE_CMD_JUMP_TO_BOOTLOADER ; 
 int /*<<< orphan*/  ZIIRAVE_CMD_RESET_PROCESSOR ; 
 int ZIIRAVE_FIRM_PKT_DATA_SIZE ; 
 int be16_to_cpu (void*) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct ihex_binrec const* ihex_next_binrec (struct ihex_binrec const*) ; 
 int /*<<< orphan*/  kfree (struct ihex_binrec const*) ; 
 struct ihex_binrec const* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 
 int ziirave_firm_verify (struct watchdog_device*,struct firmware const*) ; 
 int ziirave_firm_write_byte (struct watchdog_device*,int /*<<< orphan*/ ,int,int) ; 
 int ziirave_firm_write_pkt (struct watchdog_device*,struct ihex_binrec const*) ; 

__attribute__((used)) static int ziirave_firm_upload(struct watchdog_device *wdd,
			       const struct firmware *fw)
{
	struct i2c_client *client = to_i2c_client(wdd->parent);
	int ret, words_till_page_break;
	const struct ihex_binrec *rec;
	struct ihex_binrec *rec_new;

	ret = ziirave_firm_write_byte(wdd, ZIIRAVE_CMD_JUMP_TO_BOOTLOADER, 1,
				      false);
	if (ret)
		return ret;

	msleep(500);

	ret = ziirave_firm_write_byte(wdd, ZIIRAVE_CMD_DOWNLOAD_START, 1, true);
	if (ret)
		return ret;

	msleep(500);

	for (rec = (void *)fw->data; rec; rec = ihex_next_binrec(rec)) {
		/* Zero length marks end of records */
		if (!be16_to_cpu(rec->len))
			break;

		/* Check max data size */
		if (be16_to_cpu(rec->len) > ZIIRAVE_FIRM_PKT_DATA_SIZE) {
			dev_err(&client->dev, "Firmware packet too long (%d)\n",
				be16_to_cpu(rec->len));
			return -EMSGSIZE;
		}

		/* Calculate words till page break */
		words_till_page_break = (64 - ((be32_to_cpu(rec->addr) >> 1) &
					 0x3f));
		if ((be16_to_cpu(rec->len) >> 1) > words_till_page_break) {
			/*
			 * Data in passes page boundary, so we need to split in
			 * two blocks of data. Create a packet with the first
			 * block of data.
			 */
			rec_new = kzalloc(sizeof(struct ihex_binrec) +
					  (words_till_page_break << 1),
					  GFP_KERNEL);
			if (!rec_new)
				return -ENOMEM;

			rec_new->len = cpu_to_be16(words_till_page_break << 1);
			rec_new->addr = rec->addr;
			memcpy(rec_new->data, rec->data,
			       be16_to_cpu(rec_new->len));

			ret = ziirave_firm_write_pkt(wdd, rec_new);
			kfree(rec_new);
			if (ret)
				return ret;

			/* Create a packet with the second block of data */
			rec_new = kzalloc(sizeof(struct ihex_binrec) +
					  be16_to_cpu(rec->len) -
					  (words_till_page_break << 1),
					  GFP_KERNEL);
			if (!rec_new)
				return -ENOMEM;

			/* Remaining bytes */
			rec_new->len = rec->len -
				       cpu_to_be16(words_till_page_break << 1);

			rec_new->addr = cpu_to_be32(be32_to_cpu(rec->addr) +
					(words_till_page_break << 1));

			memcpy(rec_new->data,
			       rec->data + (words_till_page_break << 1),
			       be16_to_cpu(rec_new->len));

			ret = ziirave_firm_write_pkt(wdd, rec_new);
			kfree(rec_new);
			if (ret)
				return ret;
		} else {
			ret = ziirave_firm_write_pkt(wdd, rec);
			if (ret)
				return ret;
		}
	}

	/* For end of download, the length field will be set to 0 */
	rec_new = kzalloc(sizeof(struct ihex_binrec) + 1, GFP_KERNEL);
	if (!rec_new)
		return -ENOMEM;

	ret = ziirave_firm_write_pkt(wdd, rec_new);
	kfree(rec_new);
	if (ret) {
		dev_err(&client->dev, "Failed to send EMPTY packet: %d\n", ret);
		return ret;
	}

	/* This sleep seems to be required */
	msleep(20);

	/* Start firmware verification */
	ret = ziirave_firm_verify(wdd, fw);
	if (ret) {
		dev_err(&client->dev,
			"Failed to verify firmware: %d\n", ret);
		return ret;
	}

	/* End download operation */
	ret = ziirave_firm_write_byte(wdd, ZIIRAVE_CMD_DOWNLOAD_END, 1, false);
	if (ret)
		return ret;

	/* Reset the processor */
	ret = ziirave_firm_write_byte(wdd, ZIIRAVE_CMD_RESET_PROCESSOR, 1,
				      false);
	if (ret)
		return ret;

	msleep(500);

	return 0;
}