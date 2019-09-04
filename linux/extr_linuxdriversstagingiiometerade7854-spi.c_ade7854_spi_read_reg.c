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
typedef  int u32 ;
typedef  int u16 ;
struct spi_transfer {int* tx_buf; int bits_per_word; int len; int* rx_buf; } ;
struct iio_dev {int dummy; } ;
struct device {int dummy; } ;
struct ade7854_state {int* tx; int* rx; int /*<<< orphan*/  buf_lock; TYPE_1__* spi; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ADE7854_READ_REG ; 
 int /*<<< orphan*/  ARRAY_SIZE (struct spi_transfer*) ; 
 int be16_to_cpup (int /*<<< orphan*/  const*) ; 
 int be32_to_cpup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct ade7854_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int spi_sync_transfer (TYPE_1__*,struct spi_transfer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ade7854_spi_read_reg(struct device *dev,
				u16 reg_address,
				u32 *val,
				int bits)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ade7854_state *st = iio_priv(indio_dev);
	int ret;
	struct spi_transfer xfers[] = {
		{
			.tx_buf = st->tx,
			.bits_per_word = 8,
			.len = 3,
		}, {
			.rx_buf = st->rx,
			.bits_per_word = 8,
			.len = bits,
		}
	};

	mutex_lock(&st->buf_lock);

	st->tx[0] = ADE7854_READ_REG;
	st->tx[1] = (reg_address >> 8) & 0xFF;
	st->tx[2] = reg_address & 0xFF;

	ret = spi_sync_transfer(st->spi, xfers, ARRAY_SIZE(xfers));
	if (ret < 0) {
		dev_err(&st->spi->dev, "problem when reading register 0x%02X",
			reg_address);
		goto unlock;
	}

	switch (bits) {
	case 8:
		*val = st->rx[0];
		break;
	case 16:
		*val = be16_to_cpup((const __be16 *)st->rx);
		break;
	case 24:
		*val = (st->rx[0] << 16) | (st->rx[1] << 8) | st->rx[2];
		break;
	case 32:
		*val = be32_to_cpup((const __be32 *)st->rx);
		break;
	}

unlock:
	mutex_unlock(&st->buf_lock);
	return ret;
}