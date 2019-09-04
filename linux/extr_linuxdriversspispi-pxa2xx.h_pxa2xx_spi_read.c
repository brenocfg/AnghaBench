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
typedef  int /*<<< orphan*/  u32 ;
struct driver_data {unsigned int ioaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_readl (unsigned int) ; 

__attribute__((used)) static inline u32 pxa2xx_spi_read(const struct driver_data *drv_data,
				  unsigned reg)
{
	return __raw_readl(drv_data->ioaddr + reg);
}