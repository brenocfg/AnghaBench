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
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_dev {int dummy; } ;
struct eeprom_93cx6 {int reg_data_in; int reg_data_out; int reg_data_clock; int reg_chip_select; struct rt2x00_dev* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  E2PROM_CSR ; 
 int /*<<< orphan*/  E2PROM_CSR_CHIP_SELECT ; 
 int /*<<< orphan*/  E2PROM_CSR_DATA_CLOCK ; 
 int /*<<< orphan*/  E2PROM_CSR_DATA_IN ; 
 int /*<<< orphan*/  E2PROM_CSR_DATA_OUT ; 
 int /*<<< orphan*/  rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt2800pci_eepromregister_read(struct eeprom_93cx6 *eeprom)
{
	struct rt2x00_dev *rt2x00dev = eeprom->data;
	u32 reg;

	reg = rt2x00mmio_register_read(rt2x00dev, E2PROM_CSR);

	eeprom->reg_data_in = !!rt2x00_get_field32(reg, E2PROM_CSR_DATA_IN);
	eeprom->reg_data_out = !!rt2x00_get_field32(reg, E2PROM_CSR_DATA_OUT);
	eeprom->reg_data_clock =
	    !!rt2x00_get_field32(reg, E2PROM_CSR_DATA_CLOCK);
	eeprom->reg_chip_select =
	    !!rt2x00_get_field32(reg, E2PROM_CSR_CHIP_SELECT);
}