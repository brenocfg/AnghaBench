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
typedef  int /*<<< orphan*/  value ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct altera_pcie {int dummy; } ;

/* Variables and functions */
 scalar_t__ PCIE_CAP_OFFSET ; 
 int _altera_pcie_cfg_write (struct altera_pcie*,int /*<<< orphan*/ ,unsigned int,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int altera_write_cap_word(struct altera_pcie *pcie, u8 busno,
				 unsigned int devfn, int offset, u16 value)
{
	return _altera_pcie_cfg_write(pcie, busno, devfn,
				      PCIE_CAP_OFFSET + offset, sizeof(value),
				      value);
}