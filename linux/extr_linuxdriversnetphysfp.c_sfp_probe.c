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
struct sfp {int max_power_mW; int state; int /*<<< orphan*/  sfp_bus; int /*<<< orphan*/  dev; struct sfp** gpio; int /*<<< orphan*/  poll; int /*<<< orphan*/  get_state; int /*<<< orphan*/  set_state; struct sff_data* type; } ;
struct sff_data {int gpios; } ;
struct TYPE_3__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_device_id {struct sff_data* data; } ;
struct i2c_adapter {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 scalar_t__ GPIOD_IN ; 
 int GPIO_MAX ; 
 size_t GPIO_MODDEF0 ; 
 size_t GPIO_RATE_SELECT ; 
 size_t GPIO_TX_DISABLE ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (struct sfp*) ; 
 int PTR_ERR (struct sfp*) ; 
 int SFP_F_RATE_SELECT ; 
 int SFP_F_TX_DISABLE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_property_read_u32 (TYPE_1__*,char*,int*) ; 
 int devm_add_action (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sfp*) ; 
 struct sfp* devm_gpiod_get_optional (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct sfp*) ; 
 scalar_t__* gpio_flags ; 
 int /*<<< orphan*/ * gpio_of_names ; 
 scalar_t__ gpiod_get_value_cansleep (struct sfp*) ; 
 int gpiod_to_irq (struct sfp*) ; 
 int /*<<< orphan*/  i2c_put_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct i2c_adapter* of_find_i2c_adapter_by_node (struct device_node*) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sfp*) ; 
 int /*<<< orphan*/  poll_jiffies ; 
 int /*<<< orphan*/  sff_gpio_get_state ; 
 struct sfp* sfp_alloc (TYPE_1__*) ; 
 int /*<<< orphan*/  sfp_cleanup ; 
 struct sff_data sfp_data ; 
 int sfp_get_state (struct sfp*) ; 
 int /*<<< orphan*/  sfp_gpio_get_state ; 
 int /*<<< orphan*/  sfp_gpio_set_state ; 
 int sfp_i2c_configure (struct sfp*,struct i2c_adapter*) ; 
 int /*<<< orphan*/  sfp_irq ; 
 int /*<<< orphan*/  sfp_module_ops ; 
 int /*<<< orphan*/  sfp_module_tx_disable (struct sfp*) ; 
 int /*<<< orphan*/  sfp_of_match ; 
 int /*<<< orphan*/  sfp_register_socket (int /*<<< orphan*/ ,struct sfp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sfp_set_state (struct sfp*,int) ; 
 int /*<<< orphan*/  system_wq ; 

__attribute__((used)) static int sfp_probe(struct platform_device *pdev)
{
	const struct sff_data *sff;
	struct sfp *sfp;
	bool poll = false;
	int irq, err, i;

	sfp = sfp_alloc(&pdev->dev);
	if (IS_ERR(sfp))
		return PTR_ERR(sfp);

	platform_set_drvdata(pdev, sfp);

	err = devm_add_action(sfp->dev, sfp_cleanup, sfp);
	if (err < 0)
		return err;

	sff = sfp->type = &sfp_data;

	if (pdev->dev.of_node) {
		struct device_node *node = pdev->dev.of_node;
		const struct of_device_id *id;
		struct i2c_adapter *i2c;
		struct device_node *np;

		id = of_match_node(sfp_of_match, node);
		if (WARN_ON(!id))
			return -EINVAL;

		sff = sfp->type = id->data;

		np = of_parse_phandle(node, "i2c-bus", 0);
		if (!np) {
			dev_err(sfp->dev, "missing 'i2c-bus' property\n");
			return -ENODEV;
		}

		i2c = of_find_i2c_adapter_by_node(np);
		of_node_put(np);
		if (!i2c)
			return -EPROBE_DEFER;

		err = sfp_i2c_configure(sfp, i2c);
		if (err < 0) {
			i2c_put_adapter(i2c);
			return err;
		}
	}

	for (i = 0; i < GPIO_MAX; i++)
		if (sff->gpios & BIT(i)) {
			sfp->gpio[i] = devm_gpiod_get_optional(sfp->dev,
					   gpio_of_names[i], gpio_flags[i]);
			if (IS_ERR(sfp->gpio[i]))
				return PTR_ERR(sfp->gpio[i]);
		}

	sfp->get_state = sfp_gpio_get_state;
	sfp->set_state = sfp_gpio_set_state;

	/* Modules that have no detect signal are always present */
	if (!(sfp->gpio[GPIO_MODDEF0]))
		sfp->get_state = sff_gpio_get_state;

	device_property_read_u32(&pdev->dev, "maximum-power-milliwatt",
				 &sfp->max_power_mW);
	if (!sfp->max_power_mW)
		sfp->max_power_mW = 1000;

	dev_info(sfp->dev, "Host maximum power %u.%uW\n",
		 sfp->max_power_mW / 1000, (sfp->max_power_mW / 100) % 10);

	/* Get the initial state, and always signal TX disable,
	 * since the network interface will not be up.
	 */
	sfp->state = sfp_get_state(sfp) | SFP_F_TX_DISABLE;

	if (sfp->gpio[GPIO_RATE_SELECT] &&
	    gpiod_get_value_cansleep(sfp->gpio[GPIO_RATE_SELECT]))
		sfp->state |= SFP_F_RATE_SELECT;
	sfp_set_state(sfp, sfp->state);
	sfp_module_tx_disable(sfp);

	for (i = 0; i < GPIO_MAX; i++) {
		if (gpio_flags[i] != GPIOD_IN || !sfp->gpio[i])
			continue;

		irq = gpiod_to_irq(sfp->gpio[i]);
		if (!irq) {
			poll = true;
			continue;
		}

		err = devm_request_threaded_irq(sfp->dev, irq, NULL, sfp_irq,
						IRQF_ONESHOT |
						IRQF_TRIGGER_RISING |
						IRQF_TRIGGER_FALLING,
						dev_name(sfp->dev), sfp);
		if (err)
			poll = true;
	}

	if (poll)
		mod_delayed_work(system_wq, &sfp->poll, poll_jiffies);

	/* We could have an issue in cases no Tx disable pin is available or
	 * wired as modules using a laser as their light source will continue to
	 * be active when the fiber is removed. This could be a safety issue and
	 * we should at least warn the user about that.
	 */
	if (!sfp->gpio[GPIO_TX_DISABLE])
		dev_warn(sfp->dev,
			 "No tx_disable pin: SFP modules will always be emitting.\n");

	sfp->sfp_bus = sfp_register_socket(sfp->dev, sfp, &sfp_module_ops);
	if (!sfp->sfp_bus)
		return -ENOMEM;

	return 0;
}