#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct spi_xcomm {struct i2c_client* i2c; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct spi_master {int num_chipselect; int mode_bits; TYPE_1__ dev; int /*<<< orphan*/  transfer_one_message; int /*<<< orphan*/  flags; int /*<<< orphan*/  bits_per_word_mask; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct i2c_client {TYPE_2__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int SPI_3WIRE ; 
 int /*<<< orphan*/  SPI_BPW_MASK (int) ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int /*<<< orphan*/  SPI_MASTER_HALF_DUPLEX ; 
 int devm_spi_register_master (TYPE_2__*,struct spi_master*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct spi_master*) ; 
 struct spi_master* spi_alloc_master (TYPE_2__*,int) ; 
 struct spi_xcomm* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 
 int /*<<< orphan*/  spi_xcomm_transfer_one ; 

__attribute__((used)) static int spi_xcomm_probe(struct i2c_client *i2c,
	const struct i2c_device_id *id)
{
	struct spi_xcomm *spi_xcomm;
	struct spi_master *master;
	int ret;

	master = spi_alloc_master(&i2c->dev, sizeof(*spi_xcomm));
	if (!master)
		return -ENOMEM;

	spi_xcomm = spi_master_get_devdata(master);
	spi_xcomm->i2c = i2c;

	master->num_chipselect = 16;
	master->mode_bits = SPI_CPHA | SPI_CPOL | SPI_3WIRE;
	master->bits_per_word_mask = SPI_BPW_MASK(8);
	master->flags = SPI_MASTER_HALF_DUPLEX;
	master->transfer_one_message = spi_xcomm_transfer_one;
	master->dev.of_node = i2c->dev.of_node;
	i2c_set_clientdata(i2c, master);

	ret = devm_spi_register_master(&i2c->dev, master);
	if (ret < 0)
		spi_master_put(master);

	return ret;
}