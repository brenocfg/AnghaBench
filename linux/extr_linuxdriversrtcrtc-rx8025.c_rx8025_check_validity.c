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
struct rx8025_data {int /*<<< orphan*/  client; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int RX8025_BIT_CTRL2_PON ; 
 int RX8025_BIT_CTRL2_VDET ; 
 int RX8025_BIT_CTRL2_XST ; 
 int /*<<< orphan*/  RX8025_REG_CTRL2 ; 
 struct rx8025_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int rx8025_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rx8025_check_validity(struct device *dev)
{
	struct rx8025_data *rx8025 = dev_get_drvdata(dev);
	int ctrl2;

	ctrl2 = rx8025_read_reg(rx8025->client, RX8025_REG_CTRL2);
	if (ctrl2 < 0)
		return ctrl2;

	if (ctrl2 & RX8025_BIT_CTRL2_VDET)
		dev_warn(dev, "power voltage drop detected\n");

	if (ctrl2 & RX8025_BIT_CTRL2_PON) {
		dev_warn(dev, "power-on reset detected, date is invalid\n");
		return -EINVAL;
	}

	if (!(ctrl2 & RX8025_BIT_CTRL2_XST)) {
		dev_warn(dev, "crystal stopped, date is invalid\n");
		return -EINVAL;
	}

	return 0;
}