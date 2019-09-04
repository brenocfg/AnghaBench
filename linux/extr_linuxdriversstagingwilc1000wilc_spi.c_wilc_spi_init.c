#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct wilc_spi {int dummy; } ;
struct wilc {int /*<<< orphan*/  dev; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int crc_off; int has_thrpt_enh; } ;

/* Variables and functions */
 int /*<<< orphan*/  WILC_SPI_PROTOCOL_OFFSET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_1__ g_spi ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_internal_read (struct wilc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  spi_internal_write (struct wilc*,int /*<<< orphan*/ ,int) ; 
 struct spi_device* to_spi_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wilc_spi_read_reg (struct wilc*,int,int*) ; 

__attribute__((used)) static int wilc_spi_init(struct wilc *wilc, bool resume)
{
	struct spi_device *spi = to_spi_device(wilc->dev);
	u32 reg;
	u32 chipid;
	static int isinit;

	if (isinit) {
		if (!wilc_spi_read_reg(wilc, 0x1000, &chipid)) {
			dev_err(&spi->dev, "Fail cmd read chip id...\n");
			return 0;
		}
		return 1;
	}

	memset(&g_spi, 0, sizeof(struct wilc_spi));

	/*
	 * configure protocol
	 */
	g_spi.crc_off = 0;

	/*
	 * TODO: We can remove the CRC trials if there is a definite
	 * way to reset
	 */
	/* the SPI to it's initial value. */
	if (!spi_internal_read(wilc, WILC_SPI_PROTOCOL_OFFSET, &reg)) {
		/*
		 * Read failed. Try with CRC off. This might happen when module
		 * is removed but chip isn't reset
		 */
		g_spi.crc_off = 1;
		dev_err(&spi->dev,
			"Failed read with CRC on, retrying with CRC off\n");
		if (!spi_internal_read(wilc, WILC_SPI_PROTOCOL_OFFSET, &reg)) {
			/*
			 * Read failed with both CRC on and off,
			 * something went bad
			 */
			dev_err(&spi->dev, "Failed internal read protocol\n");
			return 0;
		}
	}
	if (g_spi.crc_off == 0) {
		reg &= ~0xc; /* disable crc checking */
		reg &= ~0x70;
		reg |= (0x5 << 4);
		if (!spi_internal_write(wilc, WILC_SPI_PROTOCOL_OFFSET, reg)) {
			dev_err(&spi->dev,
				"[wilc spi %d]: Failed internal write reg\n",
				__LINE__);
			return 0;
		}
		g_spi.crc_off = 1;
	}

	/*
	 * make sure can read back chip id correctly
	 */
	if (!wilc_spi_read_reg(wilc, 0x1000, &chipid)) {
		dev_err(&spi->dev, "Fail cmd read chip id...\n");
		return 0;
	}

	g_spi.has_thrpt_enh = 1;

	isinit = 1;

	return 1;
}