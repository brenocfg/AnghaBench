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
typedef  int /*<<< orphan*/  keyrecord_t ;

/* Variables and functions */
 scalar_t__ TEENSY_KEY ; 
 int /*<<< orphan*/  bootloader_jump () ; 
 int /*<<< orphan*/  clear_keyboard () ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  wait_ms (int) ; 

void action_function(keyrecord_t *event, uint8_t id, uint8_t opt)
{
   
    if (id == TEENSY_KEY) {
        clear_keyboard();
        print("\n\nJump to bootloader... ");
        wait_ms(250);
        bootloader_jump(); // should not return
        print("not supported.\n");
    }
}