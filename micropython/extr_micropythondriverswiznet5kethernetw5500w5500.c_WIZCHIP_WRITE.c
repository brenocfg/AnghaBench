#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* _deselect ) () ;int /*<<< orphan*/  (* _select ) () ;} ;
struct TYPE_4__ {TYPE_1__ CS; } ;

/* Variables and functions */
 int /*<<< orphan*/  Chip_SSP_WriteFrames_Blocking (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  LPC_SSP0 ; 
 TYPE_2__ WIZCHIP ; 
 int /*<<< orphan*/  WIZCHIP_CRITICAL_ENTER () ; 
 int /*<<< orphan*/  WIZCHIP_CRITICAL_EXIT () ; 
 int _W5500_SPI_VDM_OP_ ; 
 int _W5500_SPI_WRITE_ ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

void     WIZCHIP_WRITE(uint32_t AddrSel, uint8_t wb )
{
   uint8_t spi_data[4];

   WIZCHIP_CRITICAL_ENTER();
   WIZCHIP.CS._select();

   AddrSel |= (_W5500_SPI_WRITE_ | _W5500_SPI_VDM_OP_);

   //WIZCHIP.IF.SPI._write_byte((AddrSel & 0x00FF0000) >> 16);
   //WIZCHIP.IF.SPI._write_byte((AddrSel & 0x0000FF00) >>  8);
   //WIZCHIP.IF.SPI._write_byte((AddrSel & 0x000000FF) >>  0);
   //WIZCHIP.IF.SPI._write_byte(wb);
   spi_data[0] = (AddrSel & 0x00FF0000) >> 16;
   spi_data[1] = (AddrSel & 0x0000FF00) >> 8;
   spi_data[2] = (AddrSel & 0x000000FF) >> 0;
   spi_data[3] = wb;
   Chip_SSP_WriteFrames_Blocking(LPC_SSP0, spi_data, 4);

   WIZCHIP.CS._deselect();
   WIZCHIP_CRITICAL_EXIT();
}