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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFA384X_INW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 prism2_read_fid_reg(struct net_device *dev, u16 reg)
{
#ifdef EXTRA_FID_READ_TESTS
	u16 val, val2, val3;
	int i;

	for (i = 0; i < 10; i++) {
		val = HFA384X_INW(reg);
		val2 = HFA384X_INW(reg);
		val3 = HFA384X_INW(reg);

		if (val == val2 && val == val3)
			return val;

		printk(KERN_DEBUG "%s: detected fid change (try=%d, reg=%04x):"
		       " %04x %04x %04x\n",
		       dev->name, i, reg, val, val2, val3);
		if ((val == val2 || val == val3) && val != 0)
			return val;
		if (val2 == val3 && val2 != 0)
			return val2;
	}
	printk(KERN_WARNING "%s: Uhhuh.. could not read good fid from reg "
	       "%04x (%04x %04x %04x)\n", dev->name, reg, val, val2, val3);
	return val;
#else /* EXTRA_FID_READ_TESTS */
	return HFA384X_INW(reg);
#endif /* EXTRA_FID_READ_TESTS */
}