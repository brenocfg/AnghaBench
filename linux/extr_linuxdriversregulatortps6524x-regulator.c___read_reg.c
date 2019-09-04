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
typedef  int /*<<< orphan*/  t ;
struct tps6524x {int /*<<< orphan*/  dev; int /*<<< orphan*/  spi; } ;
struct spi_transfer {int* tx_buf; int len; int bits_per_word; int* rx_buf; } ;
struct spi_message {int dummy; } ;

/* Variables and functions */
 int CMD_READ (int) ; 
 int EINVAL ; 
 int EIO ; 
 int STAT_CLK ; 
 int STAT_INVALID ; 
 int STAT_WRITE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  memset (struct spi_transfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 

__attribute__((used)) static int __read_reg(struct tps6524x *hw, int reg)
{
	int error = 0;
	u16 cmd = CMD_READ(reg), in;
	u8 status;
	struct spi_message m;
	struct spi_transfer t[3];

	spi_message_init(&m);
	memset(t, 0, sizeof(t));

	t[0].tx_buf = &cmd;
	t[0].len = 2;
	t[0].bits_per_word = 12;
	spi_message_add_tail(&t[0], &m);

	t[1].rx_buf = &in;
	t[1].len = 2;
	t[1].bits_per_word = 16;
	spi_message_add_tail(&t[1], &m);

	t[2].rx_buf = &status;
	t[2].len = 1;
	t[2].bits_per_word = 4;
	spi_message_add_tail(&t[2], &m);

	error = spi_sync(hw->spi, &m);
	if (error < 0)
		return error;

	dev_dbg(hw->dev, "read reg %d, data %x, status %x\n",
		reg, in, status);

	if (!(status & STAT_CLK) || (status & STAT_WRITE))
		return -EIO;

	if (status & STAT_INVALID)
		return -EINVAL;

	return in;
}