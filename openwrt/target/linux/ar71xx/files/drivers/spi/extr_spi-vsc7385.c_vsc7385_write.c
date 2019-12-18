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
typedef  int u32 ;
typedef  int /*<<< orphan*/  t ;
struct vsc7385 {int /*<<< orphan*/  lock; int /*<<< orphan*/  spi; } ;
struct spi_transfer {int* tx_buf; int len; } ;
struct spi_message {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VSC73XX_CMD_MODE_WRITE ; 
 int /*<<< orphan*/  memset (struct spi_transfer**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 
 int /*<<< orphan*/  vsc7385_is_addr_valid (int,int) ; 
 int vsc7385_make_addr (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int vsc7385_write(struct vsc7385 *vsc, u8 block, u8 subblock, u8 reg,
			 u32 value)
{
	u8 cmd[2];
	u8 buf[4];
	struct spi_transfer t[2];
	struct spi_message m;
	int err;

	if (!vsc7385_is_addr_valid(block, subblock))
		return -EINVAL;

	spi_message_init(&m);

	memset(&t, 0, sizeof(t));

	t[0].tx_buf = cmd;
	t[0].len = sizeof(cmd);
	spi_message_add_tail(&t[0], &m);

	t[1].tx_buf = buf;
	t[1].len = sizeof(buf);
	spi_message_add_tail(&t[1], &m);

	cmd[0] = vsc7385_make_addr(VSC73XX_CMD_MODE_WRITE, block, subblock);
	cmd[1] = reg;

	buf[0] = (value >> 24) & 0xff;
	buf[1] = (value >> 16) & 0xff;
	buf[2] = (value >> 8) & 0xff;
	buf[3] = value & 0xff;

	mutex_lock(&vsc->lock);
	err = spi_sync(vsc->spi, &m);
	mutex_unlock(&vsc->lock);

	return err;
}