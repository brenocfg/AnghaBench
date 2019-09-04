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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  registers_t ;

/* Variables and functions */
 int /*<<< orphan*/  int_to_ascii (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kprint (char*) ; 
 int /*<<< orphan*/  port_byte_in (int) ; 
 int /*<<< orphan*/  print_letter (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void keyboard_callback(registers_t regs) {
    /* The PIC leaves us the scancode in port 0x60 */
    u8 scancode = port_byte_in(0x60);
    char *sc_ascii;
    int_to_ascii(scancode, sc_ascii);
    kprint("Keyboard scancode: ");
    kprint(sc_ascii);
    kprint(", ");
    print_letter(scancode);
    kprint("\n");
}