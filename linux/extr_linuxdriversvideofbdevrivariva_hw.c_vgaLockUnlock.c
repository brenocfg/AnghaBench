#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int U008 ;
struct TYPE_3__ {int /*<<< orphan*/  PCIO; } ;
typedef  TYPE_1__ RIVA_HW_INST ;

/* Variables and functions */
 int VGA_RD08 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VGA_WR08 (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void vgaLockUnlock
(
    RIVA_HW_INST *chip,
    int           Lock
)
{
    U008 cr11;
    VGA_WR08(chip->PCIO, 0x3D4, 0x11);
    cr11 = VGA_RD08(chip->PCIO, 0x3D5);
    if(Lock) cr11 |= 0x80;
    else cr11 &= ~0x80;
    VGA_WR08(chip->PCIO, 0x3D5, cr11);
}