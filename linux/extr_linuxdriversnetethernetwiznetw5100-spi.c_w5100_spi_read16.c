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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int w5100_spi_read (struct net_device*,scalar_t__) ; 

__attribute__((used)) static int w5100_spi_read16(struct net_device *ndev, u32 addr)
{
	u16 data;
	int ret;

	ret = w5100_spi_read(ndev, addr);
	if (ret < 0)
		return ret;
	data = ret << 8;
	ret = w5100_spi_read(ndev, addr + 1);

	return ret < 0 ? ret : data | ret;
}