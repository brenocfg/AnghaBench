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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int CTRL_HI_X ; 
 int CTRL_HI_Y ; 
 int CTRL_LO_DFR ; 
 int CTRL_LO_SER ; 
 int /*<<< orphan*/  ETS_GPIO_INTR_DISABLE () ; 
 int /*<<< orphan*/  ETS_GPIO_INTR_ENABLE () ; 
 int /*<<< orphan*/  GPIO_REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_STATUS_W1TC_ADDRESS ; 
 int /*<<< orphan*/  PLATFORM_GPIO_HIGH ; 
 int /*<<< orphan*/  PLATFORM_GPIO_LOW ; 
 int /*<<< orphan*/  _cs_pin ; 
 size_t _irq_pin ; 
 int /*<<< orphan*/  _readLoop (int,int) ; 
 int /*<<< orphan*/ * pin_num ; 
 int /*<<< orphan*/  platform_gpio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_spi_send_recv (int,int,int) ; 
 int /*<<< orphan*/  transfer16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void getRaw(uint16_t *vi, uint16_t *vj) {
  // Implementation based on TI Technical Note http://www.ti.com/lit/an/sbaa036/sbaa036.pdf

  // Disable interrupt: reading position generates false interrupt
  ETS_GPIO_INTR_DISABLE();

  platform_gpio_write(_cs_pin, PLATFORM_GPIO_LOW);
  platform_spi_send_recv(1, 8 , CTRL_HI_X | CTRL_LO_DFR);  // Send first control int
  *vi = _readLoop(CTRL_HI_X | CTRL_LO_DFR, 255);
  *vj = _readLoop(CTRL_HI_Y | CTRL_LO_DFR, 255);

  // Turn off ADC by issuing one more read (throwaway)
  // This needs to be done, because PD=0b11 (needed for MODE_DFR) will disable PENIRQ
  platform_spi_send_recv(1, 8 , 0);  // Maintain 16-clocks/conversion; _readLoop always ends after issuing a control int
  platform_spi_send_recv(1, 8 , CTRL_HI_Y | CTRL_LO_SER);
  transfer16(0);  // Flush last read, just to be sure

  platform_gpio_write(_cs_pin, PLATFORM_GPIO_HIGH);

  // Clear interrupt status
  GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, BIT(pin_num[_irq_pin]));
  // Enable interrupt again
  ETS_GPIO_INTR_ENABLE();
}