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
typedef  int u32 ;
struct lp3943_pwm_map {int* output; int num_outputs; } ;
struct lp3943_pwm {struct lp3943_platform_data* pdata; } ;
struct lp3943_platform_data {struct lp3943_pwm_map** pwms; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
typedef  enum lp3943_pwm_output { ____Placeholder_lp3943_pwm_output } lp3943_pwm_output ;

/* Variables and functions */
 int EINVAL ; 
 int ENODATA ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int LP3943_NUM_PWMS ; 
 int* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_get_property (struct device_node*,char const* const,int*) ; 
 int of_property_read_u32_array (struct device_node*,char const* const,int*,int) ; 

__attribute__((used)) static int lp3943_pwm_parse_dt(struct device *dev,
			       struct lp3943_pwm *lp3943_pwm)
{
	static const char * const name[] = { "ti,pwm0", "ti,pwm1", };
	struct device_node *node = dev->of_node;
	struct lp3943_platform_data *pdata;
	struct lp3943_pwm_map *pwm_map;
	enum lp3943_pwm_output *output;
	int i, err, proplen, count = 0;
	u32 num_outputs;

	if (!node)
		return -EINVAL;

	pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return -ENOMEM;

	/*
	 * Read the output map configuration from the device tree.
	 * Each of the two PWM generators can drive zero or more outputs.
	 */

	for (i = 0; i < LP3943_NUM_PWMS; i++) {
		if (!of_get_property(node, name[i], &proplen))
			continue;

		num_outputs = proplen / sizeof(u32);
		if (num_outputs == 0)
			continue;

		output = devm_kcalloc(dev, num_outputs, sizeof(*output),
				      GFP_KERNEL);
		if (!output)
			return -ENOMEM;

		err = of_property_read_u32_array(node, name[i], output,
						 num_outputs);
		if (err)
			return err;

		pwm_map = devm_kzalloc(dev, sizeof(*pwm_map), GFP_KERNEL);
		if (!pwm_map)
			return -ENOMEM;

		pwm_map->output = output;
		pwm_map->num_outputs = num_outputs;
		pdata->pwms[i] = pwm_map;

		count++;
	}

	if (count == 0)
		return -ENODATA;

	lp3943_pwm->pdata = pdata;
	return 0;
}