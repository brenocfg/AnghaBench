#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uniphier_aio_chip {int num_plls; TYPE_2__* plls; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int enable; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 

__attribute__((used)) static bool is_valid_pll(struct uniphier_aio_chip *chip, int pll_id)
{
	struct device *dev = &chip->pdev->dev;

	if (pll_id < 0 || chip->num_plls <= pll_id) {
		dev_err(dev, "PLL(%d) is not supported\n", pll_id);
		return false;
	}

	return chip->plls[pll_id].enable;
}