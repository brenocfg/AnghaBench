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
typedef  int u32 ;
struct mt7621_pcie {int dummy; } ;

/* Variables and functions */
 int pcie_read (struct mt7621_pcie*,int) ; 
 int /*<<< orphan*/  pcie_write (struct mt7621_pcie*,int,int) ; 

void
set_pcie_phy(struct mt7621_pcie *pcie, u32 offset,
	     int start_b, int bits, int val)
{
	u32 reg = pcie_read(pcie, offset);

	reg &= ~(((1 << bits) - 1) << start_b);
	reg |= val << start_b;
	pcie_write(pcie, reg, offset);
}