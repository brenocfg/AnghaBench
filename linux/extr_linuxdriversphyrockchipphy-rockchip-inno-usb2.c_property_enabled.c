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
struct usb2phy_reg {unsigned int bitstart; unsigned int enable; int /*<<< orphan*/  offset; int /*<<< orphan*/  bitend; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 unsigned int GENMASK (int /*<<< orphan*/ ,unsigned int) ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static inline bool property_enabled(struct regmap *base,
				    const struct usb2phy_reg *reg)
{
	int ret;
	unsigned int tmp, orig;
	unsigned int mask = GENMASK(reg->bitend, reg->bitstart);

	ret = regmap_read(base, reg->offset, &orig);
	if (ret)
		return false;

	tmp = (orig & mask) >> reg->bitstart;
	return tmp == reg->enable;
}