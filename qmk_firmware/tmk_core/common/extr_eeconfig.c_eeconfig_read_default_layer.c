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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  EECONFIG_DEFAULT_LAYER ; 
 int /*<<< orphan*/  eeprom_read_byte (int /*<<< orphan*/ ) ; 

uint8_t eeconfig_read_default_layer(void) { return eeprom_read_byte(EECONFIG_DEFAULT_LAYER); }