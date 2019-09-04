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
struct pci_dev {int device; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV_ARCH_03 ; 
 int /*<<< orphan*/  NV_ARCH_04 ; 
 int /*<<< orphan*/  NV_ARCH_10 ; 
 int /*<<< orphan*/  NV_ARCH_20 ; 
 int /*<<< orphan*/  NV_ARCH_30 ; 

__attribute__((used)) static u32 riva_get_arch(struct pci_dev *pd)
{
    	u32 arch = 0;

	switch (pd->device & 0x0ff0) {
		case 0x0100:   /* GeForce 256 */
		case 0x0110:   /* GeForce2 MX */
		case 0x0150:   /* GeForce2 */
		case 0x0170:   /* GeForce4 MX */
		case 0x0180:   /* GeForce4 MX (8x AGP) */
		case 0x01A0:   /* nForce */
		case 0x01F0:   /* nForce2 */
		     arch =  NV_ARCH_10;
		     break;
		case 0x0200:   /* GeForce3 */
		case 0x0250:   /* GeForce4 Ti */
		case 0x0280:   /* GeForce4 Ti (8x AGP) */
		     arch =  NV_ARCH_20;
		     break;
		case 0x0300:   /* GeForceFX 5800 */
		case 0x0310:   /* GeForceFX 5600 */
		case 0x0320:   /* GeForceFX 5200 */
		case 0x0330:   /* GeForceFX 5900 */
		case 0x0340:   /* GeForceFX 5700 */
		     arch =  NV_ARCH_30;
		     break;
		case 0x0020:   /* TNT, TNT2 */
		     arch =  NV_ARCH_04;
		     break;
		case 0x0010:   /* Riva128 */
		     arch =  NV_ARCH_03;
		     break;
		default:   /* unknown architecture */
		     break;
	}
	return arch;
}