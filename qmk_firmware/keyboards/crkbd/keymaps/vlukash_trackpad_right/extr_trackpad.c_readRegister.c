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
typedef  int uint8_t ;

/* Variables and functions */
 int SPI_TransferByte (int) ; 
 int /*<<< orphan*/  TP_CS_HI ; 
 int /*<<< orphan*/  TP_CS_LO ; 

uint8_t readRegister(uint8_t address) {
  uint8_t data;

  TP_CS_LO;

  // Read the data
  SPI_TransferByte(address);
  data = SPI_TransferByte(0x00);

  TP_CS_HI;

  return data;
}