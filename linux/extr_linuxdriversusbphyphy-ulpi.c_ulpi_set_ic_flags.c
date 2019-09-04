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
struct usb_phy {int flags; } ;

/* Variables and functions */
 int ULPI_IC_AUTORESUME ; 
 int ULPI_IC_EXTVBUS_INDINV ; 
 int ULPI_IC_IND_PASSTHRU ; 
 int ULPI_IC_PROTECT_DIS ; 
 int /*<<< orphan*/  ULPI_IFC_CTRL ; 
 unsigned int ULPI_IFC_CTRL_AUTORESUME ; 
 unsigned int ULPI_IFC_CTRL_EXTERNAL_VBUS ; 
 unsigned int ULPI_IFC_CTRL_PASSTHRU ; 
 unsigned int ULPI_IFC_CTRL_PROTECT_IFC_DISABLE ; 
 int usb_phy_io_write (struct usb_phy*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ulpi_set_ic_flags(struct usb_phy *phy)
{
	unsigned int flags = 0;

	if (phy->flags & ULPI_IC_AUTORESUME)
		flags |= ULPI_IFC_CTRL_AUTORESUME;

	if (phy->flags & ULPI_IC_EXTVBUS_INDINV)
		flags |= ULPI_IFC_CTRL_EXTERNAL_VBUS;

	if (phy->flags & ULPI_IC_IND_PASSTHRU)
		flags |= ULPI_IFC_CTRL_PASSTHRU;

	if (phy->flags & ULPI_IC_PROTECT_DIS)
		flags |= ULPI_IFC_CTRL_PROTECT_IFC_DISABLE;

	return usb_phy_io_write(phy, flags, ULPI_IFC_CTRL);
}