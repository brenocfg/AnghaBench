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
struct mdio_gpio_info {int /*<<< orphan*/  mdo; void* mdio; void* mdc; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  MDIO_GPIO_MDC ; 
 int /*<<< orphan*/  MDIO_GPIO_MDIO ; 
 int /*<<< orphan*/  MDIO_GPIO_MDO ; 
 int PTR_ERR (void*) ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 void* devm_gpiod_get_index (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_gpiod_get_index_optional (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mdio_gpio_get_data(struct device *dev,
			      struct mdio_gpio_info *bitbang)
{
	bitbang->mdc = devm_gpiod_get_index(dev, NULL, MDIO_GPIO_MDC,
					    GPIOD_OUT_LOW);
	if (IS_ERR(bitbang->mdc))
		return PTR_ERR(bitbang->mdc);

	bitbang->mdio = devm_gpiod_get_index(dev, NULL, MDIO_GPIO_MDIO,
					     GPIOD_IN);
	if (IS_ERR(bitbang->mdio))
		return PTR_ERR(bitbang->mdio);

	bitbang->mdo = devm_gpiod_get_index_optional(dev, NULL, MDIO_GPIO_MDO,
						     GPIOD_OUT_LOW);
	return PTR_ERR_OR_ZERO(bitbang->mdo);
}