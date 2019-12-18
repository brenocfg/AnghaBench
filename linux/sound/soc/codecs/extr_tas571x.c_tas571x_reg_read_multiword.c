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
typedef  unsigned int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct i2c_msg {int len; unsigned int* buf; scalar_t__ flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  send_buf ;

/* Variables and functions */
 int ARRAY_SIZE (struct i2c_msg*) ; 
 int EIO ; 
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 scalar_t__ I2C_M_RD ; 
 long get_unaligned_be32 (unsigned int*) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  kfree (unsigned int*) ; 
 unsigned int* kzalloc (unsigned int,int) ; 

__attribute__((used)) static int tas571x_reg_read_multiword(struct i2c_client *client,
		unsigned int reg, long values[], size_t len)
{
	unsigned int i;
	uint8_t send_buf;
	uint8_t *recv_buf, *p;
	struct i2c_msg msgs[2];
	unsigned int recv_size = len * sizeof(uint32_t);
	int ret;

	recv_buf = kzalloc(recv_size, GFP_KERNEL | GFP_DMA);
	if (!recv_buf)
		return -ENOMEM;

	send_buf = reg;

	msgs[0].addr = client->addr;
	msgs[0].len = sizeof(send_buf);
	msgs[0].buf = &send_buf;
	msgs[0].flags = 0;

	msgs[1].addr = client->addr;
	msgs[1].len = recv_size;
	msgs[1].buf = recv_buf;
	msgs[1].flags = I2C_M_RD;

	ret = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	if (ret < 0)
		goto err_ret;
	else if (ret != ARRAY_SIZE(msgs)) {
		ret = -EIO;
		goto err_ret;
	}

	for (i = 0, p = recv_buf; i < len; i++, p += sizeof(uint32_t))
		values[i] = get_unaligned_be32(p);

err_ret:
	kfree(recv_buf);
	return ret;
}