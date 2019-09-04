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
typedef  scalar_t__ u16 ;
struct dln2_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLN2_SPI_ATTR_LEAVE_SS_LOW ; 
 scalar_t__ DLN2_SPI_MAX_XFER_SIZE ; 
 int EINVAL ; 
 int dln2_spi_read_one (struct dln2_spi*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int dln2_spi_read_write_one (struct dln2_spi*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int dln2_spi_write_one (struct dln2_spi*,int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dln2_spi_rdwr(struct dln2_spi *dln2, const u8 *tx_data,
			 u8 *rx_data, u16 data_len, u8 attr) {
	int ret;
	u16 len;
	u8 temp_attr;
	u16 remaining = data_len;
	u16 offset;

	do {
		if (remaining > DLN2_SPI_MAX_XFER_SIZE) {
			len = DLN2_SPI_MAX_XFER_SIZE;
			temp_attr = DLN2_SPI_ATTR_LEAVE_SS_LOW;
		} else {
			len = remaining;
			temp_attr = attr;
		}

		offset = data_len - remaining;

		if (tx_data && rx_data) {
			ret = dln2_spi_read_write_one(dln2,
						      tx_data + offset,
						      rx_data + offset,
						      len, temp_attr);
		} else if (tx_data) {
			ret = dln2_spi_write_one(dln2,
						 tx_data + offset,
						 len, temp_attr);
		} else if (rx_data) {
			ret = dln2_spi_read_one(dln2,
						rx_data + offset,
						len, temp_attr);
		 } else {
			return -EINVAL;
		 }

		if (ret < 0)
			return ret;

		remaining -= len;
	} while (remaining);

	return 0;
}