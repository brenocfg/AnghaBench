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
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int modes; int /*<<< orphan*/  buffer; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  name; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct i2c_device_id {int /*<<< orphan*/  name; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct ad5933_state {int vref_mv; int /*<<< orphan*/  reg; int /*<<< orphan*/  poll_time_jiffies; int /*<<< orphan*/  work; int /*<<< orphan*/  ctrl_lb; scalar_t__ mclk_hz; int /*<<< orphan*/  lock; struct i2c_client* client; } ;
struct ad5933_platform_data {int vref_mv; scalar_t__ ext_clk_Hz; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD5933_CTRL_EXT_SYSCLK ; 
 int /*<<< orphan*/  AD5933_CTRL_INT_SYSCLK ; 
 scalar_t__ AD5933_INT_OSC_FREQ_Hz ; 
 int /*<<< orphan*/  AD5933_POLL_TIME_ms ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int INDIO_BUFFER_SOFTWARE ; 
 int INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ad5933_calc_out_ranges (struct ad5933_state*) ; 
 int /*<<< orphan*/  ad5933_channels ; 
 struct ad5933_platform_data ad5933_default_pdata ; 
 int /*<<< orphan*/  ad5933_info ; 
 int ad5933_register_ring_funcs_and_init (struct iio_dev*) ; 
 int ad5933_setup (struct ad5933_state*) ; 
 int /*<<< orphan*/  ad5933_work ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct ad5933_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int iio_device_register (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_kfifo_free (int /*<<< orphan*/ ) ; 
 struct ad5933_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int regulator_get_voltage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad5933_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	int ret, voltage_uv = 0;
	struct ad5933_platform_data *pdata = dev_get_platdata(&client->dev);
	struct ad5933_state *st;
	struct iio_dev *indio_dev;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*st));
	if (!indio_dev)
		return -ENOMEM;

	st = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	st->client = client;

	mutex_init(&st->lock);

	if (!pdata)
		pdata = &ad5933_default_pdata;

	st->reg = devm_regulator_get(&client->dev, "vdd");
	if (IS_ERR(st->reg))
		return PTR_ERR(st->reg);

	ret = regulator_enable(st->reg);
	if (ret) {
		dev_err(&client->dev, "Failed to enable specified VDD supply\n");
		return ret;
	}
	voltage_uv = regulator_get_voltage(st->reg);

	if (voltage_uv)
		st->vref_mv = voltage_uv / 1000;
	else
		st->vref_mv = pdata->vref_mv;

	if (pdata->ext_clk_Hz) {
		st->mclk_hz = pdata->ext_clk_Hz;
		st->ctrl_lb = AD5933_CTRL_EXT_SYSCLK;
	} else {
		st->mclk_hz = AD5933_INT_OSC_FREQ_Hz;
		st->ctrl_lb = AD5933_CTRL_INT_SYSCLK;
	}

	ad5933_calc_out_ranges(st);
	INIT_DELAYED_WORK(&st->work, ad5933_work);
	st->poll_time_jiffies = msecs_to_jiffies(AD5933_POLL_TIME_ms);

	indio_dev->dev.parent = &client->dev;
	indio_dev->info = &ad5933_info;
	indio_dev->name = id->name;
	indio_dev->modes = (INDIO_BUFFER_SOFTWARE | INDIO_DIRECT_MODE);
	indio_dev->channels = ad5933_channels;
	indio_dev->num_channels = ARRAY_SIZE(ad5933_channels);

	ret = ad5933_register_ring_funcs_and_init(indio_dev);
	if (ret)
		goto error_disable_reg;

	ret = ad5933_setup(st);
	if (ret)
		goto error_unreg_ring;

	ret = iio_device_register(indio_dev);
	if (ret)
		goto error_unreg_ring;

	return 0;

error_unreg_ring:
	iio_kfifo_free(indio_dev->buffer);
error_disable_reg:
	regulator_disable(st->reg);

	return ret;
}