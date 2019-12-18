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
 int PCICR ; 
 int PCMSK1 ; 
 int /*<<< orphan*/  WD_AVR_RESET () ; 
 int /*<<< orphan*/  change_driver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_vusb () ; 
 int /*<<< orphan*/  init_vusb () ; 
 int insomniac ; 
 int /*<<< orphan*/  iwrap_call () ; 
 int /*<<< orphan*/  iwrap_driver () ; 
 int /*<<< orphan*/  iwrap_kill () ; 
 int /*<<< orphan*/  iwrap_unpair () ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  vusb_driver () ; 

__attribute__((used)) static bool console_command(uint8_t c) {
    switch (c) {
        case 'h':
        case '?':
            print("\nCommands for Bluetooth(WT12/iWRAP):\n");
            print("r: reset. software reset by watchdog\n");
            print("i: insomniac. prevent KB from sleeping\n");
            print("c: iwrap_call. CALL for BT connection.\n");
#ifdef PROTOCOL_VUSB
            print("u: USB mode. switch to USB.\n");
            print("w: BT mode. switch to Bluetooth.\n");
#endif
            print("k: kill first connection.\n");
            print("Del: unpair first pairing.\n");
            print("\n");
            return 0;
        case 'r':
            print("reset\n");
            WD_AVR_RESET();
            return 1;
        case 'i':
            insomniac = !insomniac;
            if (insomniac)
                print("insomniac\n");
            else
                print("not insomniac\n");
            return 1;
        case 'c':
            print("iwrap_call()\n");
            iwrap_call();
            return 1;
#ifdef PROTOCOL_VUSB
        case 'u':
            print("USB mode\n");
            init_vusb();
            change_driver(vusb_driver());
            // iwrap_kill();
            // iwrap_sleep();
            // disable suart receive interrut(PC5/PCINT13)
            PCMSK1 &= ~(0b00100000);
            PCICR &= ~(0b00000010);
            return 1;
        case 'w':
            print("iWRAP mode\n");
            change_driver(iwrap_driver());
            disable_vusb();
            // enable suart receive interrut(PC5/PCINT13)
            PCMSK1 |= 0b00100000;
            PCICR |= 0b00000010;
            return 1;
#endif
        case 'k':
            print("kill\n");
            iwrap_kill();
            return 1;
        case 0x7F:  // DELETE
            print("unpair\n");
            iwrap_unpair();
            return 1;
    }
    return 0;
}