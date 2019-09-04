#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int IO; int /*<<< orphan*/  PCIO; int /*<<< orphan*/  (* LockUnlock ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ RIVA_HW_INST ;

/* Variables and functions */
 void* VGA_RD08 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VGA_WR08 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void SetStartAddress3
(
    RIVA_HW_INST *chip,
    unsigned      start
)
{
    int offset = start >> 2;
    int pan    = (start & 3) << 1;
    unsigned char tmp;

    /*
     * Unlock extended registers.
     */
    chip->LockUnlock(chip, 0);
    /*
     * Set start address.
     */
    VGA_WR08(chip->PCIO, 0x3D4, 0x0D); VGA_WR08(chip->PCIO, 0x3D5, offset);
    offset >>= 8;
    VGA_WR08(chip->PCIO, 0x3D4, 0x0C); VGA_WR08(chip->PCIO, 0x3D5, offset);
    offset >>= 8;
    VGA_WR08(chip->PCIO, 0x3D4, 0x19); tmp = VGA_RD08(chip->PCIO, 0x3D5);
    VGA_WR08(chip->PCIO, 0x3D5, (offset & 0x01F) | (tmp & ~0x1F));
    VGA_WR08(chip->PCIO, 0x3D4, 0x2D); tmp = VGA_RD08(chip->PCIO, 0x3D5);
    VGA_WR08(chip->PCIO, 0x3D5, (offset & 0x60) | (tmp & ~0x60));
    /*
     * 4 pixel pan register.
     */
    offset = VGA_RD08(chip->PCIO, chip->IO + 0x0A);
    VGA_WR08(chip->PCIO, 0x3C0, 0x13);
    VGA_WR08(chip->PCIO, 0x3C0, pan);
}