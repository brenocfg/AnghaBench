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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  asus_hides_smbus ; 
 scalar_t__ asus_rcba_base ; 
 scalar_t__ likely (int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void asus_hides_smbus_lpc_ich6_resume_early(struct pci_dev *dev)
{
	u32 val;

	if (likely(!asus_hides_smbus || !asus_rcba_base))
		return;

	/* read the Function Disable register, dword mode only */
	val = readl(asus_rcba_base + 0x3418);

	/* enable the SMBus device */
	writel(val & 0xFFFFFFF7, asus_rcba_base + 0x3418);
}