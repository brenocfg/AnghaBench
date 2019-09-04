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
struct spi_device {int bits_per_word; int max_speed_hz; int mode; int /*<<< orphan*/  dev; } ;
struct rtc_device {int dummy; } ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct rtc_device*) ; 
 int PTR_ERR (struct rtc_device*) ; 
 int RTC_ADDR_CTRL ; 
 int RTC_CMD_READ ; 
 int RTC_CMD_WRITE ; 
 int RTC_CMD_WRITE_DISABLE ; 
 int SPI_CPHA ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct rtc_device* devm_rtc_device_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds1302_rtc_ops ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct spi_device*) ; 
 int spi_write_then_read (struct spi_device*,int*,int,int*,int) ; 

__attribute__((used)) static int ds1302_probe(struct spi_device *spi)
{
	struct rtc_device	*rtc;
	u8		addr;
	u8		buf[4];
	u8		*bp;
	int		status;

	/* Sanity check board setup data.  This may be hooked up
	 * in 3wire mode, but we don't care.  Note that unless
	 * there's an inverter in place, this needs SPI_CS_HIGH!
	 */
	if (spi->bits_per_word && (spi->bits_per_word != 8)) {
		dev_err(&spi->dev, "bad word length\n");
		return -EINVAL;
	} else if (spi->max_speed_hz > 2000000) {
		dev_err(&spi->dev, "speed is too high\n");
		return -EINVAL;
	} else if (spi->mode & SPI_CPHA) {
		dev_err(&spi->dev, "bad mode\n");
		return -EINVAL;
	}

	addr = RTC_ADDR_CTRL << 1 | RTC_CMD_READ;
	status = spi_write_then_read(spi, &addr, sizeof(addr), buf, 1);
	if (status < 0) {
		dev_err(&spi->dev, "control register read error %d\n",
				status);
		return status;
	}

	if ((buf[0] & ~RTC_CMD_WRITE_DISABLE) != 0) {
		status = spi_write_then_read(spi, &addr, sizeof(addr), buf, 1);
		if (status < 0) {
			dev_err(&spi->dev, "control register read error %d\n",
					status);
			return status;
		}

		if ((buf[0] & ~RTC_CMD_WRITE_DISABLE) != 0) {
			dev_err(&spi->dev, "junk in control register\n");
			return -ENODEV;
		}
	}
	if (buf[0] == 0) {
		bp = buf;
		*bp++ = RTC_ADDR_CTRL << 1 | RTC_CMD_WRITE;
		*bp++ = RTC_CMD_WRITE_DISABLE;

		status = spi_write_then_read(spi, buf, 2, NULL, 0);
		if (status < 0) {
			dev_err(&spi->dev, "control register write error %d\n",
					status);
			return status;
		}

		addr = RTC_ADDR_CTRL << 1 | RTC_CMD_READ;
		status = spi_write_then_read(spi, &addr, sizeof(addr), buf, 1);
		if (status < 0) {
			dev_err(&spi->dev,
					"error %d reading control register\n",
					status);
			return status;
		}

		if (buf[0] != RTC_CMD_WRITE_DISABLE) {
			dev_err(&spi->dev, "failed to detect chip\n");
			return -ENODEV;
		}
	}

	spi_set_drvdata(spi, spi);

	rtc = devm_rtc_device_register(&spi->dev, "ds1302",
			&ds1302_rtc_ops, THIS_MODULE);
	if (IS_ERR(rtc)) {
		status = PTR_ERR(rtc);
		dev_err(&spi->dev, "error %d registering rtc\n", status);
		return status;
	}

	return 0;
}