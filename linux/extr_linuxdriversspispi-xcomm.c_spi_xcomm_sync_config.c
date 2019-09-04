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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  unsigned int uint16_t ;
struct spi_xcomm {unsigned int settings; unsigned int chipselect; int /*<<< orphan*/  i2c; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_XCOMM_CMD_UPDATE_CONFIG ; 
 unsigned int SPI_XCOMM_SETTINGS_LEN_OFFSET ; 
 int i2c_master_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_unaligned_be16 (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int spi_xcomm_sync_config(struct spi_xcomm *spi_xcomm, unsigned int len)
{
	uint16_t settings;
	uint8_t *buf = spi_xcomm->buf;

	settings = spi_xcomm->settings;
	settings |= len << SPI_XCOMM_SETTINGS_LEN_OFFSET;

	buf[0] = SPI_XCOMM_CMD_UPDATE_CONFIG;
	put_unaligned_be16(settings, &buf[1]);
	put_unaligned_be16(spi_xcomm->chipselect, &buf[3]);

	return i2c_master_send(spi_xcomm->i2c, buf, 5);
}