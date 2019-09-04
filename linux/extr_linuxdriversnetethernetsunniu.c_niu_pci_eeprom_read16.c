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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct niu {int dummy; } ;

/* Variables and functions */
 int niu_pci_eeprom_read (struct niu*,scalar_t__) ; 

__attribute__((used)) static int niu_pci_eeprom_read16(struct niu *np, u32 off)
{
	int err = niu_pci_eeprom_read(np, off);
	u16 val;

	if (err < 0)
		return err;
	val = (err << 8);
	err = niu_pci_eeprom_read(np, off + 1);
	if (err < 0)
		return err;
	val |= (err & 0xff);

	return val;
}