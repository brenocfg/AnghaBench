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

/* Variables and functions */
 void const* PIN_CS ; 
 void const* PIN_EN ; 
 void const* PIN_IRQ ; 
 void* SPI_HANDLE ; 

void SpiInit(void *spi, const void *pin_cs, const void *pin_en, const void *pin_irq) {
    SPI_HANDLE = spi;
    PIN_CS = pin_cs;
    PIN_EN = pin_en;
    PIN_IRQ = pin_irq;
}