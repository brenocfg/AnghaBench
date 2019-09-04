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
struct seq_file {int dummy; } ;
struct pinctrl_dev {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void abx500_gpio_dbg_show_one(struct seq_file *s,
					    struct pinctrl_dev *pctldev,
					    struct gpio_chip *chip,
					    unsigned offset, unsigned gpio)
{
}