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
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 int DDRB ; 
 int DDRD ; 
 int /*<<< orphan*/  KUCHOSAURONAD0_UNICODE_MODE ; 
 int PORTB ; 
 int PORTD ; 
 int /*<<< orphan*/  eeconfig_read_user () ; 
 int /*<<< orphan*/  get_unicode_input_mode () ; 
 int /*<<< orphan*/  matrix_init_keymap () ; 
 int /*<<< orphan*/  set_unicode_input_mode (int /*<<< orphan*/ ) ; 
 TYPE_1__ userspace_config ; 

void matrix_init_user(void) {
  userspace_config.raw = eeconfig_read_user();

  #ifdef BOOTLOADER_CATERINA
    DDRD &= ~(1<<5);
    PORTD &= ~(1<<5);

    DDRB &= ~(1<<0);
    PORTB &= ~(1<<0);
  #endif

  #if (defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE))
    set_unicode_input_mode(KUCHOSAURONAD0_UNICODE_MODE);
    get_unicode_input_mode();
  #endif //UNICODE_ENABLE
  matrix_init_keymap();
}