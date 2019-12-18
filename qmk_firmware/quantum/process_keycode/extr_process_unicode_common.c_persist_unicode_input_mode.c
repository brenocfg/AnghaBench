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
struct TYPE_2__ {int /*<<< orphan*/  input_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  EECONFIG_UNICODEMODE ; 
 int /*<<< orphan*/  eeprom_update_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ unicode_config ; 

void persist_unicode_input_mode(void) { eeprom_update_byte(EECONFIG_UNICODEMODE, unicode_config.input_mode); }