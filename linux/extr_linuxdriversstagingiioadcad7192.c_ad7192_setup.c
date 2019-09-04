#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct iio_dev {TYPE_2__* channels; } ;
struct TYPE_10__ {TYPE_3__* spi; } ;
struct ad7192_state {int devid; int mode; int conf; int f_order; int** scale_avail; TYPE_4__ sd; scalar_t__ int_vref_mv; int /*<<< orphan*/  mclk; } ;
struct ad7192_platform_data {int clock_source_sel; scalar_t__ burnout_curr_en; scalar_t__ chop_en; scalar_t__ buf_en; scalar_t__ unipolar_en; scalar_t__ sinc3_en; scalar_t__ refin2_en; scalar_t__ rej60_en; int /*<<< orphan*/  ext_clk_hz; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int realbits; } ;
struct TYPE_8__ {TYPE_1__ scan_type; } ;

/* Variables and functions */
#define  AD7192_CLK_EXT_MCLK1_2 131 
#define  AD7192_CLK_EXT_MCLK2 130 
#define  AD7192_CLK_INT 129 
#define  AD7192_CLK_INT_CO 128 
 int AD7192_CONF_BUF ; 
 int AD7192_CONF_BURN ; 
 int AD7192_CONF_CHOP ; 
 int AD7192_CONF_GAIN (int /*<<< orphan*/ ) ; 
 int AD7192_CONF_REFSEL ; 
 int AD7192_CONF_UNIPOLAR ; 
 int AD7192_ID_MASK ; 
 int /*<<< orphan*/  AD7192_INT_FREQ_MHZ ; 
 int AD7192_MODE_CLKSRC (int) ; 
 int /*<<< orphan*/  AD7192_MODE_IDLE ; 
 int AD7192_MODE_RATE (int) ; 
 int AD7192_MODE_REJ60 ; 
 int AD7192_MODE_SEL (int /*<<< orphan*/ ) ; 
 int AD7192_MODE_SINC3 ; 
 int /*<<< orphan*/  AD7192_REG_CONF ; 
 int /*<<< orphan*/  AD7192_REG_ID ; 
 int /*<<< orphan*/  AD7192_REG_MODE ; 
 int ARRAY_SIZE (int**) ; 
 int EINVAL ; 
 int ID_AD7195 ; 
 int ad7192_calibrate_all (struct ad7192_state*) ; 
 int /*<<< orphan*/  ad7192_valid_external_frequency (int /*<<< orphan*/ ) ; 
 int ad_sd_read_reg (TYPE_4__*,int /*<<< orphan*/ ,int,int*) ; 
 int ad_sd_reset (TYPE_4__*,int) ; 
 int ad_sd_write_reg (TYPE_4__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 int do_div (unsigned long long,int) ; 
 struct iio_dev* spi_get_drvdata (TYPE_3__*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ad7192_setup(struct ad7192_state *st,
			const struct ad7192_platform_data *pdata)
{
	struct iio_dev *indio_dev = spi_get_drvdata(st->sd.spi);
	unsigned long long scale_uv;
	int i, ret, id;

	/* reset the serial interface */
	ret = ad_sd_reset(&st->sd, 48);
	if (ret < 0)
		goto out;
	usleep_range(500, 1000); /* Wait for at least 500us */

	/* write/read test for device presence */
	ret = ad_sd_read_reg(&st->sd, AD7192_REG_ID, 1, &id);
	if (ret)
		goto out;

	id &= AD7192_ID_MASK;

	if (id != st->devid)
		dev_warn(&st->sd.spi->dev, "device ID query failed (0x%X)\n",
			 id);

	switch (pdata->clock_source_sel) {
	case AD7192_CLK_INT:
	case AD7192_CLK_INT_CO:
		st->mclk = AD7192_INT_FREQ_MHZ;
		break;
	case AD7192_CLK_EXT_MCLK1_2:
	case AD7192_CLK_EXT_MCLK2:
		if (ad7192_valid_external_frequency(pdata->ext_clk_hz)) {
			st->mclk = pdata->ext_clk_hz;
			break;
		}
		dev_err(&st->sd.spi->dev, "Invalid frequency setting %u\n",
			pdata->ext_clk_hz);
		ret = -EINVAL;
		goto out;
	default:
		ret = -EINVAL;
		goto out;
	}

	st->mode = AD7192_MODE_SEL(AD7192_MODE_IDLE) |
		AD7192_MODE_CLKSRC(pdata->clock_source_sel) |
		AD7192_MODE_RATE(480);

	st->conf = AD7192_CONF_GAIN(0);

	if (pdata->rej60_en)
		st->mode |= AD7192_MODE_REJ60;

	if (pdata->sinc3_en)
		st->mode |= AD7192_MODE_SINC3;

	if (pdata->refin2_en && st->devid != ID_AD7195)
		st->conf |= AD7192_CONF_REFSEL;

	if (pdata->chop_en) {
		st->conf |= AD7192_CONF_CHOP;
		if (pdata->sinc3_en)
			st->f_order = 3; /* SINC 3rd order */
		else
			st->f_order = 4; /* SINC 4th order */
	} else {
		st->f_order = 1;
	}

	if (pdata->buf_en)
		st->conf |= AD7192_CONF_BUF;

	if (pdata->unipolar_en)
		st->conf |= AD7192_CONF_UNIPOLAR;

	if (pdata->burnout_curr_en && pdata->buf_en && !pdata->chop_en) {
		st->conf |= AD7192_CONF_BURN;
	} else if (pdata->burnout_curr_en) {
		dev_warn(&st->sd.spi->dev,
			 "Can't enable burnout currents: see CHOP or buffer\n");
	}

	ret = ad_sd_write_reg(&st->sd, AD7192_REG_MODE, 3, st->mode);
	if (ret)
		goto out;

	ret = ad_sd_write_reg(&st->sd, AD7192_REG_CONF, 3, st->conf);
	if (ret)
		goto out;

	ret = ad7192_calibrate_all(st);
	if (ret)
		goto out;

	/* Populate available ADC input ranges */
	for (i = 0; i < ARRAY_SIZE(st->scale_avail); i++) {
		scale_uv = ((u64)st->int_vref_mv * 100000000)
			>> (indio_dev->channels[0].scan_type.realbits -
			((st->conf & AD7192_CONF_UNIPOLAR) ? 0 : 1));
		scale_uv >>= i;

		st->scale_avail[i][1] = do_div(scale_uv, 100000000) * 10;
		st->scale_avail[i][0] = scale_uv;
	}

	return 0;
out:
	dev_err(&st->sd.spi->dev, "setup failed\n");
	return ret;
}