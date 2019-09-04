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
typedef  int /*<<< orphan*/  u16 ;
struct ssb_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,char*) ; 
 int ssb_read32 (struct ssb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ssb_wait_bits(struct ssb_device *dev, u16 reg, u32 bitmask,
			 int timeout, int set)
{
	int i;
	u32 val;

	for (i = 0; i < timeout; i++) {
		val = ssb_read32(dev, reg);
		if (set) {
			if ((val & bitmask) == bitmask)
				return 0;
		} else {
			if (!(val & bitmask))
				return 0;
		}
		udelay(10);
	}
	dev_err(dev->dev,
		"Timeout waiting for bitmask %08X on register %04X to %s\n",
		bitmask, reg, set ? "set" : "clear");

	return -ETIMEDOUT;
}