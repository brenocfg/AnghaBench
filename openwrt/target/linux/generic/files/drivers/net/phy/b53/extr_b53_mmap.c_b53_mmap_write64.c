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
typedef  int u8 ;
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct b53_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  b53_mmap_write32 (struct b53_device*,int,int,scalar_t__) ; 

__attribute__((used)) static int b53_mmap_write64(struct b53_device *dev, u8 page, u8 reg,
			     u64 value)
{
	u32 hi, lo;

	hi = (u32)(value >> 32);
	lo = (u32)value;

	if (WARN_ON(reg % 4))
		return -EINVAL;

	b53_mmap_write32(dev, page, reg, lo);
	b53_mmap_write32(dev, page, reg + 4, hi);

	return 0;
}