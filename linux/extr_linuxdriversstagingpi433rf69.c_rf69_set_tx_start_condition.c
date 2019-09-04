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
struct spi_device {int /*<<< orphan*/  dev; } ;
typedef  enum tx_start_condition { ____Placeholder_tx_start_condition } tx_start_condition ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MASK_FIFO_THRESH_TXSTART ; 
 int /*<<< orphan*/  REG_FIFO_THRESH ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
#define  fifo_level 129 
#define  fifo_not_empty 128 
 int rf69_clear_bit (struct spi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rf69_set_bit (struct spi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rf69_set_tx_start_condition(struct spi_device *spi,
				enum tx_start_condition tx_start_condition)
{
	switch (tx_start_condition) {
	case fifo_level:
		return rf69_clear_bit(spi, REG_FIFO_THRESH,
				      MASK_FIFO_THRESH_TXSTART);
	case fifo_not_empty:
		return rf69_set_bit(spi, REG_FIFO_THRESH,
				    MASK_FIFO_THRESH_TXSTART);
	default:
		dev_dbg(&spi->dev, "set: illegal input param");
		return -EINVAL;
	}
}