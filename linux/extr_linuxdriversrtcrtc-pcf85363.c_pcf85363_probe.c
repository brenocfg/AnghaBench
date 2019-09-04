#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct pcf85363 {TYPE_1__* rtc; int /*<<< orphan*/ * dev; TYPE_1__* regmap; } ;
struct nvmem_config {char* name; int word_size; int stride; struct pcf85363* priv; int /*<<< orphan*/  reg_write; int /*<<< orphan*/  reg_read; int /*<<< orphan*/  size; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  adapter; } ;
struct TYPE_9__ {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_FLAGS ; 
 int /*<<< orphan*/  CTRL_PIN_IO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_LOW ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  NVRAM_SIZE ; 
 int /*<<< orphan*/  PIN_IO_INTAPM ; 
 int /*<<< orphan*/  PIN_IO_INTA_OUT ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct pcf85363* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct i2c_client*) ; 
 TYPE_1__* devm_rtc_allocate_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct pcf85363*) ; 
 int /*<<< orphan*/  pcf85363_nvram_read ; 
 int /*<<< orphan*/  pcf85363_nvram_write ; 
 int /*<<< orphan*/  pcf85363_rtc_handle_irq ; 
 int /*<<< orphan*/  regmap_config ; 
 int /*<<< orphan*/  regmap_update_bits (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_nvmem_register (TYPE_1__*,struct nvmem_config*) ; 
 int /*<<< orphan*/  rtc_ops ; 
 int /*<<< orphan*/  rtc_ops_alarm ; 
 int rtc_register_device (TYPE_1__*) ; 

__attribute__((used)) static int pcf85363_probe(struct i2c_client *client,
			  const struct i2c_device_id *id)
{
	struct pcf85363 *pcf85363;
	struct nvmem_config nvmem_cfg = {
		.name = "pcf85363-",
		.word_size = 1,
		.stride = 1,
		.size = NVRAM_SIZE,
		.reg_read = pcf85363_nvram_read,
		.reg_write = pcf85363_nvram_write,
	};
	int ret;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		return -ENODEV;

	pcf85363 = devm_kzalloc(&client->dev, sizeof(struct pcf85363),
				GFP_KERNEL);
	if (!pcf85363)
		return -ENOMEM;

	pcf85363->regmap = devm_regmap_init_i2c(client, &regmap_config);
	if (IS_ERR(pcf85363->regmap)) {
		dev_err(&client->dev, "regmap allocation failed\n");
		return PTR_ERR(pcf85363->regmap);
	}

	pcf85363->dev = &client->dev;
	i2c_set_clientdata(client, pcf85363);

	pcf85363->rtc = devm_rtc_allocate_device(pcf85363->dev);
	if (IS_ERR(pcf85363->rtc))
		return PTR_ERR(pcf85363->rtc);

	pcf85363->rtc->ops = &rtc_ops;

	if (client->irq > 0) {
		regmap_write(pcf85363->regmap, CTRL_FLAGS, 0);
		regmap_update_bits(pcf85363->regmap, CTRL_PIN_IO,
				   PIN_IO_INTA_OUT, PIN_IO_INTAPM);
		ret = devm_request_threaded_irq(pcf85363->dev, client->irq,
						NULL, pcf85363_rtc_handle_irq,
						IRQF_TRIGGER_LOW | IRQF_ONESHOT,
						"pcf85363", client);
		if (ret)
			dev_warn(&client->dev, "unable to request IRQ, alarms disabled\n");
		else
			pcf85363->rtc->ops = &rtc_ops_alarm;
	}

	ret = rtc_register_device(pcf85363->rtc);

	nvmem_cfg.priv = pcf85363;
	rtc_nvmem_register(pcf85363->rtc, &nvmem_cfg);

	return ret;
}