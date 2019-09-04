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
typedef  int /*<<< orphan*/  u32 ;
struct wilc {int /*<<< orphan*/  dev; } ;
struct spi_transfer {char* tx_buf; int /*<<< orphan*/  delay_usecs; int /*<<< orphan*/  len; int /*<<< orphan*/ * rx_buf; } ;
struct spi_message {int /*<<< orphan*/  is_dma_mapped; struct spi_device* spi; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USE_SPI_DMA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct spi_message*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (struct spi_device*,struct spi_message*) ; 
 struct spi_device* to_spi_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wilc_spi_rx(struct wilc *wilc, u8 *rb, u32 rlen)
{
	struct spi_device *spi = to_spi_device(wilc->dev);
	int ret;

	if (rlen > 0) {
		struct spi_message msg;
		struct spi_transfer tr = {
			.rx_buf = rb,
			.len = rlen,
			.delay_usecs = 0,

		};
		char *t_buffer = kzalloc(rlen, GFP_KERNEL);

		if (!t_buffer)
			return -ENOMEM;

		tr.tx_buf = t_buffer;

		memset(&msg, 0, sizeof(msg));
		spi_message_init(&msg);
		msg.spi = spi;
		msg.is_dma_mapped = USE_SPI_DMA;
		spi_message_add_tail(&tr, &msg);

		ret = spi_sync(spi, &msg);
		if (ret < 0)
			dev_err(&spi->dev, "SPI transaction failed\n");
		kfree(t_buffer);
	} else {
		dev_err(&spi->dev,
			"can't read data with the following length: %u\n",
			rlen);
		ret = -EINVAL;
	}

	return ret;
}