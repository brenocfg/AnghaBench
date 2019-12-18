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
struct hw {int dummy; } ;

/* Variables and functions */
 int hw_read_pci (struct hw*,int) ; 
 int /*<<< orphan*/  hw_write_pci (struct hw*,int,int) ; 

__attribute__((used)) static int i2c_unlock(struct hw *hw)
{
	if ((hw_read_pci(hw, 0xcc) & 0xff) == 0xaa)
		return 0;

	hw_write_pci(hw, 0xcc, 0x8c);
	hw_write_pci(hw, 0xcc, 0x0e);
	if ((hw_read_pci(hw, 0xcc) & 0xff) == 0xaa)
		return 0;

	hw_write_pci(hw, 0xcc, 0xee);
	hw_write_pci(hw, 0xcc, 0xaa);
	if ((hw_read_pci(hw, 0xcc) & 0xff) == 0xaa)
		return 0;

	return -1;
}