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
typedef  int u16 ;
struct renesas_usb3 {int dummy; } ;

/* Variables and functions */
 int SSIFCMD_UDIR_U1 ; 
 int SSIFCMD_UDIR_U2 ; 
 int SSIFCMD_UREQ_U1 ; 
 int SSIFCMD_UREQ_U2 ; 
 int /*<<< orphan*/  USB3_SSIFCMD ; 
 int USB_DEV_STAT_U1_ENABLED ; 
 int USB_DEV_STAT_U2_ENABLED ; 
 int usb3_read (struct renesas_usb3*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 usb3_feature_get_un_enabled(struct renesas_usb3 *usb3)
{
	u32 mask_u2 = SSIFCMD_UDIR_U2 | SSIFCMD_UREQ_U2;
	u32 mask_u1 = SSIFCMD_UDIR_U1 | SSIFCMD_UREQ_U1;
	u32 val = usb3_read(usb3, USB3_SSIFCMD);
	u16 ret = 0;

	/* Enables {U2,U1} if the bits of UDIR and UREQ are set to 0 */
	if (!(val & mask_u2))
		ret |= 1 << USB_DEV_STAT_U2_ENABLED;
	if (!(val & mask_u1))
		ret |= 1 << USB_DEV_STAT_U1_ENABLED;

	return ret;
}