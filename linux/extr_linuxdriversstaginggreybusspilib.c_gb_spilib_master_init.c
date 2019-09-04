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
struct spilib_ops {scalar_t__ unprepare_transfer_hardware; scalar_t__ prepare_transfer_hardware; } ;
struct spi_master {int bus_num; scalar_t__ num_chipselect; int auto_runtime_pm; int /*<<< orphan*/  unprepare_transfer_hardware; int /*<<< orphan*/  prepare_transfer_hardware; int /*<<< orphan*/  transfer_one_message; int /*<<< orphan*/  setup; int /*<<< orphan*/  cleanup; int /*<<< orphan*/  bits_per_word_mask; int /*<<< orphan*/  flags; int /*<<< orphan*/  mode_bits; } ;
struct gb_spilib {scalar_t__ num_chipselect; int /*<<< orphan*/  bits_per_word_mask; int /*<<< orphan*/  flags; int /*<<< orphan*/  mode; struct spilib_ops* ops; struct device* parent; struct gb_connection* connection; } ;
struct gb_connection {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  gb_connection_set_data (struct gb_connection*,struct spi_master*) ; 
 int /*<<< orphan*/  gb_spi_cleanup ; 
 int gb_spi_get_master_config (struct gb_spilib*) ; 
 int /*<<< orphan*/  gb_spi_prepare_transfer_hardware ; 
 int /*<<< orphan*/  gb_spi_setup ; 
 int gb_spi_setup_device (struct gb_spilib*,scalar_t__) ; 
 int /*<<< orphan*/  gb_spi_transfer_one_message ; 
 int /*<<< orphan*/  gb_spi_unprepare_transfer_hardware ; 
 struct spi_master* spi_alloc_master (struct device*,int) ; 
 struct gb_spilib* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 
 int spi_register_master (struct spi_master*) ; 
 int /*<<< orphan*/  spi_unregister_master (struct spi_master*) ; 

int gb_spilib_master_init(struct gb_connection *connection, struct device *dev,
			  struct spilib_ops *ops)
{
	struct gb_spilib *spi;
	struct spi_master *master;
	int ret;
	u8 i;

	/* Allocate master with space for data */
	master = spi_alloc_master(dev, sizeof(*spi));
	if (!master) {
		dev_err(dev, "cannot alloc SPI master\n");
		return -ENOMEM;
	}

	spi = spi_master_get_devdata(master);
	spi->connection = connection;
	gb_connection_set_data(connection, master);
	spi->parent = dev;
	spi->ops = ops;

	/* get master configuration */
	ret = gb_spi_get_master_config(spi);
	if (ret)
		goto exit_spi_put;

	master->bus_num = -1; /* Allow spi-core to allocate it dynamically */
	master->num_chipselect = spi->num_chipselect;
	master->mode_bits = spi->mode;
	master->flags = spi->flags;
	master->bits_per_word_mask = spi->bits_per_word_mask;

	/* Attach methods */
	master->cleanup = gb_spi_cleanup;
	master->setup = gb_spi_setup;
	master->transfer_one_message = gb_spi_transfer_one_message;

	if (ops && ops->prepare_transfer_hardware) {
		master->prepare_transfer_hardware =
			gb_spi_prepare_transfer_hardware;
	}

	if (ops && ops->unprepare_transfer_hardware) {
		master->unprepare_transfer_hardware =
			gb_spi_unprepare_transfer_hardware;
	}

	master->auto_runtime_pm = true;

	ret = spi_register_master(master);
	if (ret < 0)
		goto exit_spi_put;

	/* now, fetch the devices configuration */
	for (i = 0; i < spi->num_chipselect; i++) {
		ret = gb_spi_setup_device(spi, i);
		if (ret < 0) {
			dev_err(dev, "failed to allocate spi device %d: %d\n",
				i, ret);
			goto exit_spi_unregister;
		}
	}

	return 0;

exit_spi_put:
	spi_master_put(master);

	return ret;

exit_spi_unregister:
	spi_unregister_master(master);

	return ret;
}