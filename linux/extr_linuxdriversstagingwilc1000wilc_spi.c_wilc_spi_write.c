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
typedef  int u32 ;
struct wilc {int /*<<< orphan*/  dev; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_DMA_EXT_WRITE ; 
 int N_OK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int spi_cmd_complete (struct wilc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int spi_data_write (struct wilc*,int /*<<< orphan*/ *,int) ; 
 struct spi_device* to_spi_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wilc_spi_write(struct wilc *wilc, u32 addr, u8 *buf, u32 size)
{
	struct spi_device *spi = to_spi_device(wilc->dev);
	int result;

	/*
	 * has to be greated than 4
	 */
	if (size <= 4)
		return 0;

	result = spi_cmd_complete(wilc, CMD_DMA_EXT_WRITE, addr, NULL, size, 0);
	if (result != N_OK) {
		dev_err(&spi->dev,
			"Failed cmd, write block (%08x)...\n", addr);
		return 0;
	}

	/*
	 * Data
	 */
	result = spi_data_write(wilc, buf, size);
	if (result != N_OK)
		dev_err(&spi->dev, "Failed block data write...\n");

	return 1;
}