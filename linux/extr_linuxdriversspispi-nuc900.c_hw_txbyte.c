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
struct nuc900_spi {unsigned int* tx; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int hw_txbyte(struct nuc900_spi *hw, int count)
{
	return hw->tx ? hw->tx[count] : 0;
}