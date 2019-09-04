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
struct device {int dummy; } ;
struct ad7606_state {int /*<<< orphan*/  gpio_os; void* gpio_frstdata; void* gpio_standby; void* gpio_range; void* gpio_reset; void* gpio_convst; struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 void* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_gpiod_get_array_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 void* devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad7606_request_gpios(struct ad7606_state *st)
{
	struct device *dev = st->dev;

	st->gpio_convst = devm_gpiod_get(dev, "conversion-start",
					 GPIOD_OUT_LOW);
	if (IS_ERR(st->gpio_convst))
		return PTR_ERR(st->gpio_convst);

	st->gpio_reset = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(st->gpio_reset))
		return PTR_ERR(st->gpio_reset);

	st->gpio_range = devm_gpiod_get_optional(dev, "range", GPIOD_OUT_LOW);
	if (IS_ERR(st->gpio_range))
		return PTR_ERR(st->gpio_range);

	st->gpio_standby = devm_gpiod_get_optional(dev, "standby",
						   GPIOD_OUT_HIGH);
	if (IS_ERR(st->gpio_standby))
		return PTR_ERR(st->gpio_standby);

	st->gpio_frstdata = devm_gpiod_get_optional(dev, "first-data",
						    GPIOD_IN);
	if (IS_ERR(st->gpio_frstdata))
		return PTR_ERR(st->gpio_frstdata);

	st->gpio_os = devm_gpiod_get_array_optional(dev, "oversampling-ratio",
			GPIOD_OUT_LOW);
	return PTR_ERR_OR_ZERO(st->gpio_os);
}