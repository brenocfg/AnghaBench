#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct b43_wldev {TYPE_1__* dfsentry; } ;
struct TYPE_2__ {unsigned int mmio32read_next; } ;

/* Variables and functions */
 unsigned int B43_MAX_MMIO_ACCESS ; 
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int sscanf (char const*,char*,unsigned int*) ; 

__attribute__((used)) static int mmio32read__write_file(struct b43_wldev *dev,
				  const char *buf, size_t count)
{
	unsigned int addr;
	int res;

	res = sscanf(buf, "0x%X", &addr);
	if (res != 1)
		return -EINVAL;
	if (addr > B43_MAX_MMIO_ACCESS)
		return -EADDRNOTAVAIL;
	if ((addr % 4) != 0)
		return -EINVAL;

	dev->dfsentry->mmio32read_next = addr;

	return 0;
}