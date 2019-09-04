#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct w5500_spi_priv {int dummy; } ;
struct w5200_spi_priv {int dummy; } ;
struct w5100_ops {int dummy; } ;
struct spi_device_id {int driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct spi_device {int /*<<< orphan*/  irq; TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  W5100 130 
#define  W5200 129 
#define  W5500 128 
 void* of_get_mac_address (int /*<<< orphan*/ ) ; 
 struct spi_device_id* spi_get_device_id (struct spi_device*) ; 
 int w5100_probe (TYPE_1__*,struct w5100_ops const*,int,void const*,int /*<<< orphan*/ ,int) ; 
 struct w5100_ops w5100_spi_ops ; 
 struct w5100_ops w5200_ops ; 
 struct w5100_ops w5500_ops ; 

__attribute__((used)) static int w5100_spi_probe(struct spi_device *spi)
{
	const struct spi_device_id *id = spi_get_device_id(spi);
	const struct w5100_ops *ops;
	int priv_size;
	const void *mac = of_get_mac_address(spi->dev.of_node);

	switch (id->driver_data) {
	case W5100:
		ops = &w5100_spi_ops;
		priv_size = 0;
		break;
	case W5200:
		ops = &w5200_ops;
		priv_size = sizeof(struct w5200_spi_priv);
		break;
	case W5500:
		ops = &w5500_ops;
		priv_size = sizeof(struct w5500_spi_priv);
		break;
	default:
		return -EINVAL;
	}

	return w5100_probe(&spi->dev, ops, priv_size, mac, spi->irq, -EINVAL);
}