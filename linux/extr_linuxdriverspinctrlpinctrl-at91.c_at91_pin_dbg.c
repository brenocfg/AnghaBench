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
struct at91_pmx_pin {int mux; int /*<<< orphan*/  conf; int /*<<< orphan*/  pin; scalar_t__ bank; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device const*,char*,scalar_t__,int /*<<< orphan*/ ,int,...) ; 

__attribute__((used)) static void at91_pin_dbg(const struct device *dev, const struct at91_pmx_pin *pin)
{
	if (pin->mux) {
		dev_dbg(dev, "pio%c%d configured as periph%c with conf = 0x%lx\n",
			pin->bank + 'A', pin->pin, pin->mux - 1 + 'A', pin->conf);
	} else {
		dev_dbg(dev, "pio%c%d configured as gpio with conf = 0x%lx\n",
			pin->bank + 'A', pin->pin, pin->conf);
	}
}