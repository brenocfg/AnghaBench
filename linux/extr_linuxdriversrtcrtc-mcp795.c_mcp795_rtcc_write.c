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
typedef  scalar_t__ u8 ;
struct spi_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ MCP795_WRITE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,scalar_t__) ; 
 int spi_write (struct spi_device*,scalar_t__*,scalar_t__) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static int mcp795_rtcc_write(struct device *dev, u8 addr, u8 *data, u8 count)
{
	struct spi_device *spi = to_spi_device(dev);
	int ret;
	u8 tx[257];

	tx[0] = MCP795_WRITE;
	tx[1] = addr;
	memcpy(&tx[2], data, count);

	ret = spi_write(spi, tx, 2 + count);

	if (ret)
		dev_err(dev, "Failed to write %d bytes to address %x.\n",
					count, addr);

	return ret;
}