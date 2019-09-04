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
typedef  unsigned int u32 ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 unsigned int B43_MAX_MMIO_ACCESS ; 
 int E2BIG ; 
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 unsigned int b43_read32 (struct b43_wldev*,unsigned int) ; 
 int /*<<< orphan*/  b43_write32 (struct b43_wldev*,unsigned int,unsigned int) ; 
 int sscanf (char const*,char*,unsigned int*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static int mmio32write__write_file(struct b43_wldev *dev,
				   const char *buf, size_t count)
{
	unsigned int addr, mask, set;
	int res;
	u32 val;

	res = sscanf(buf, "0x%X 0x%X 0x%X", &addr, &mask, &set);
	if (res != 3)
		return -EINVAL;
	if (addr > B43_MAX_MMIO_ACCESS)
		return -EADDRNOTAVAIL;
	if ((mask > 0xFFFFFFFF) || (set > 0xFFFFFFFF))
		return -E2BIG;
	if ((addr % 4) != 0)
		return -EINVAL;

	if (mask == 0)
		val = 0;
	else
		val = b43_read32(dev, addr);
	val &= mask;
	val |= set;
	b43_write32(dev, addr, val);

	return 0;
}