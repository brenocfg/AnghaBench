#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* CurrentState; int /*<<< orphan*/  PCIO; } ;
struct TYPE_4__ {int cursor1; } ;
typedef  TYPE_2__ RIVA_HW_INST ;

/* Variables and functions */
 int /*<<< orphan*/  VGA_WR08 (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ShowHideCursor
(
    RIVA_HW_INST *chip,
    int           ShowHide
)
{
    int cursor;
    cursor                      =  chip->CurrentState->cursor1;
    chip->CurrentState->cursor1 = (chip->CurrentState->cursor1 & 0xFE) |
                                  (ShowHide & 0x01);
    VGA_WR08(chip->PCIO, 0x3D4, 0x31);
    VGA_WR08(chip->PCIO, 0x3D5, chip->CurrentState->cursor1);
    return (cursor & 0x01);
}