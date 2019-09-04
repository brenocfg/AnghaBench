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
struct tiny_spi {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ TINY_SPI_STATUS ; 
 int TINY_SPI_STATUS_TXE ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int readb (scalar_t__) ; 

__attribute__((used)) static inline void tiny_spi_wait_txe(struct tiny_spi *hw)
{
	while (!(readb(hw->base + TINY_SPI_STATUS) &
		 TINY_SPI_STATUS_TXE))
		cpu_relax();
}