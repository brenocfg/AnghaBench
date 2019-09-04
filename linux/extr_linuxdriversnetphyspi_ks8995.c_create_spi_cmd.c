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
typedef  unsigned int u16 ;
struct ks8995_switch {TYPE_1__* chip; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {unsigned int addr_width; unsigned int addr_shift; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be16 (unsigned int) ; 

__attribute__((used)) static inline __be16 create_spi_cmd(struct ks8995_switch *ks, int cmd,
				    unsigned address)
{
	u16 result = cmd;

	/* make room for address (incl. address shift) */
	result <<= ks->chip->addr_width + ks->chip->addr_shift;
	/* add address */
	result |= address << ks->chip->addr_shift;
	/* SPI protocol needs big endian */
	return cpu_to_be16(result);
}