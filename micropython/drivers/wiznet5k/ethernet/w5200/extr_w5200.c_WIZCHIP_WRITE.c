#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* _deselect ) () ;int /*<<< orphan*/  (* _select ) () ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* _write_bytes ) (int*,int) ;} ;
struct TYPE_6__ {TYPE_1__ SPI; } ;
struct TYPE_8__ {TYPE_3__ CS; TYPE_2__ IF; } ;

/* Variables and functions */
 TYPE_4__ WIZCHIP ; 
 int /*<<< orphan*/  WIZCHIP_CRITICAL_ENTER () ; 
 int /*<<< orphan*/  WIZCHIP_CRITICAL_EXIT () ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 (int*,int) ; 
 int /*<<< orphan*/  stub3 () ; 

void WIZCHIP_WRITE(uint32_t AddrSel, uint8_t wb) {
    WIZCHIP_CRITICAL_ENTER();
    WIZCHIP.CS._select();

    uint8_t spi_data[5] = {
        AddrSel >> 8,
        AddrSel,
        0x80,
        0x01,
        wb,
    };
    WIZCHIP.IF.SPI._write_bytes(spi_data, 5);

    WIZCHIP.CS._deselect();
    WIZCHIP_CRITICAL_EXIT();
}