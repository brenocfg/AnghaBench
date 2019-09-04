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
typedef  int /*<<< orphan*/  ulong ;
typedef  int u32 ;
struct gasket_dev {int dummy; } ;

/* Variables and functions */
 int gasket_dev_read_32 (struct gasket_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gasket_dev_write_32 (struct gasket_dev*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void gasket_read_modify_write_32(struct gasket_dev *dev, int bar,
					       ulong location, u32 value,
					       u32 mask_width, u32 mask_shift)
{
	u32 mask, tmp;

	tmp = gasket_dev_read_32(dev, bar, location);
	mask = ((1 << mask_width) - 1) << mask_shift;
	tmp = (tmp & ~mask) | (value << mask_shift);
	gasket_dev_write_32(dev, tmp, bar, location);
}