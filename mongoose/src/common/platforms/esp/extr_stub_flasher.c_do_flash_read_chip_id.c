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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  chip_id ;

/* Variables and functions */
 int READ_PERI_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_CMD_REG (int /*<<< orphan*/ ) ; 
 int SPI_FLASH_RDID ; 
 int /*<<< orphan*/  SPI_W0_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_PERI_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  send_packet (int /*<<< orphan*/ *,int) ; 

int do_flash_read_chip_id(void) {
  uint32_t chip_id = 0;
  WRITE_PERI_REG(SPI_CMD_REG(0), SPI_FLASH_RDID);
  while (READ_PERI_REG(SPI_CMD_REG(0)) & SPI_FLASH_RDID) {
  }
  chip_id = READ_PERI_REG(SPI_W0_REG(0)) & 0xFFFFFF;
  send_packet((uint8_t *) &chip_id, sizeof(chip_id));
  return 0;
}