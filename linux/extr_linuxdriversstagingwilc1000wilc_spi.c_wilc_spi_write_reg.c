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
struct wilc {int /*<<< orphan*/  dev; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CMD_INTERNAL_WRITE ; 
 int CMD_SINGLE_WRITE ; 
 int N_OK ; 
 int /*<<< orphan*/  cpu_to_le32s (int*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int spi_cmd_complete (struct wilc*,int,int,int*,int,int) ; 
 struct spi_device* to_spi_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wilc_spi_write_reg(struct wilc *wilc, u32 addr, u32 data)
{
	struct spi_device *spi = to_spi_device(wilc->dev);
	int result = N_OK;
	u8 cmd = CMD_SINGLE_WRITE;
	u8 clockless = 0;

	cpu_to_le32s(&data);
	if (addr < 0x30) {
		/* Clockless register */
		cmd = CMD_INTERNAL_WRITE;
		clockless = 1;
	}

	result = spi_cmd_complete(wilc, cmd, addr, (u8 *)&data, 4, clockless);
	if (result != N_OK)
		dev_err(&spi->dev, "Failed cmd, write reg (%08x)...\n", addr);

	return result;
}