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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  registers_t ;

/* Variables and functions */
 scalar_t__ BACKSPACE ; 
 scalar_t__ ENTER ; 
 scalar_t__ SC_MAX ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  append (char*,char) ; 
 int /*<<< orphan*/  backspace (char*) ; 
 char* key_buffer ; 
 int /*<<< orphan*/  kprint (char*) ; 
 int /*<<< orphan*/  kprint_backspace () ; 
 scalar_t__ port_byte_in (int) ; 
 char* sc_ascii ; 
 int /*<<< orphan*/  user_input (char*) ; 

__attribute__((used)) static void keyboard_callback(registers_t *regs) {
    /* The PIC leaves us the scancode in port 0x60 */
    uint8_t scancode = port_byte_in(0x60);
    
    if (scancode > SC_MAX) return;
    if (scancode == BACKSPACE) {
        backspace(key_buffer);
        kprint_backspace();
    } else if (scancode == ENTER) {
        kprint("\n");
        user_input(key_buffer); /* kernel-controlled function */
        key_buffer[0] = '\0';
    } else {
        char letter = sc_ascii[(int)scancode];
        /* Remember that kprint only accepts char[] */
        char str[2] = {letter, '\0'};
        append(key_buffer, letter);
        kprint(str);
    }
    UNUSED(regs);
}