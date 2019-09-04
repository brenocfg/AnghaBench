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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {scalar_t__ chip_size; } ;
typedef  TYPE_1__ SpiFlashChip ;

/* Variables and functions */
 int /*<<< orphan*/  SPIRead (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  SPIWrite (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  default_init_data ; 
 int /*<<< orphan*/  ets_printf (char*) ; 
 int /*<<< orphan*/  flashchip ; 

void firmware_start(void) {
    // For SDK 1.5.2, either address has shifted and not mirrored in
    // eagle.rom.addr.v6.ld, or extra initial member was added.
    SpiFlashChip *flash = (SpiFlashChip*)(&flashchip + 4);

    char buf[128];
    SPIRead(flash->chip_size - 4 * 0x1000, buf, sizeof(buf));
    /*for (int i = 0; i < sizeof(buf); i++) {
        static char hexf[] = "%x ";
        ets_printf(hexf, buf[i]);
    }*/

    bool inited = false;
    for (int i = 0; i < sizeof(buf); i++) {
        if (buf[i] != 0xff) {
            inited = true;
            break;
        }
    }

    if (!inited) {
        static char msg[] = "Writing init data\n";
        ets_printf(msg);
        SPIRead((uint32_t)&default_init_data - 0x40200000, buf, sizeof(buf));
        SPIWrite(flash->chip_size - 4 * 0x1000, buf, sizeof(buf));
    }

    asm("j call_user_start");
}