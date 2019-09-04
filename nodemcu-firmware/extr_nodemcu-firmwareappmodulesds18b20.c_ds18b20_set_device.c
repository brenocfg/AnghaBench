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
 int /*<<< orphan*/  DS18B20_FUNC_SCRATCH_WRITE ; 
 int /*<<< orphan*/  ds18b20_bus_pin ; 
 int /*<<< orphan*/  ds18b20_device_conf ; 
 int /*<<< orphan*/  onewire_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  onewire_select (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  onewire_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  onewire_write_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ds18b20_set_device(uint8_t *ds18b20_device_rom) {
	onewire_reset(ds18b20_bus_pin);
	onewire_select(ds18b20_bus_pin, ds18b20_device_rom);
	onewire_write(ds18b20_bus_pin, DS18B20_FUNC_SCRATCH_WRITE, 0);
	onewire_write_bytes(ds18b20_bus_pin, ds18b20_device_conf, 3, 0);
}