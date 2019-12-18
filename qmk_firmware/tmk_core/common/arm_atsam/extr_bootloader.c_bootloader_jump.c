#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_16__ {int ENABLE; } ;
struct TYPE_17__ {TYPE_7__ bit; } ;
struct TYPE_14__ {scalar_t__ ENABLE; } ;
struct TYPE_15__ {TYPE_5__ bit; } ;
struct TYPE_12__ {scalar_t__ EWOFFSET; } ;
struct TYPE_13__ {TYPE_3__ bit; } ;
struct TYPE_10__ {scalar_t__ PER; scalar_t__ WINDOW; } ;
struct TYPE_11__ {TYPE_1__ bit; } ;
struct TYPE_18__ {TYPE_8__ CTRLA; TYPE_6__ SYNCBUSY; TYPE_4__ EWCTRL; TYPE_2__ CONFIG; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOOTLOADER_MAGIC ; 
 int /*<<< orphan*/ * MAGIC_ADDR ; 
 int /*<<< orphan*/  NVIC_SystemReset () ; 
 TYPE_9__* WDT ; 

void bootloader_jump(void) {
#ifdef KEYBOARD_massdrop_ctrl
    // CTRL keyboards released with bootloader version below must use RAM method. Otherwise use WDT method.
    uint8_t  ver_ram_method[] = "v2.18Jun 22 2018 17:28:08";  // The version to match (NULL terminated by compiler)
    uint8_t *ver_check        = ver_ram_method;               // Pointer to version match string for traversal
    uint8_t *ver_rom          = (uint8_t *)0x21A0;            // Pointer to address in ROM where this specific bootloader version would exist

    while (*ver_check && *ver_rom == *ver_check) {  // While there are check version characters to match and bootloader's version matches check's version
        ver_check++;                                // Move check version pointer to next character
        ver_rom++;                                  // Move ROM version pointer to next character
    }

    if (!*ver_check) {                   // If check version pointer is NULL, all characters have matched
        *MAGIC_ADDR = BOOTLOADER_MAGIC;  // Set magic number into RAM
        NVIC_SystemReset();              // Perform system reset
        while (1) {
        }  // Won't get here
    }
#endif

    WDT->CTRLA.bit.ENABLE = 0;
    while (WDT->SYNCBUSY.bit.ENABLE) {
    }
    while (WDT->CTRLA.bit.ENABLE) {
    }
    WDT->CONFIG.bit.WINDOW   = 0;
    WDT->CONFIG.bit.PER      = 0;
    WDT->EWCTRL.bit.EWOFFSET = 0;
    WDT->CTRLA.bit.ENABLE    = 1;
    while (WDT->SYNCBUSY.bit.ENABLE) {
    }
    while (!WDT->CTRLA.bit.ENABLE) {
    }
    while (1) {
    }  // Wait on timeout
}