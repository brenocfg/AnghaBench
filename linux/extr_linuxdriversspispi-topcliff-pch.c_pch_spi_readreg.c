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
struct spi_master {int dummy; } ;
struct pch_spi_data {scalar_t__ io_remap_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 struct pch_spi_data* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static inline u32 pch_spi_readreg(struct spi_master *master, int idx)
{
	struct pch_spi_data *data = spi_master_get_devdata(master);
	return ioread32(data->io_remap_addr + idx);
}