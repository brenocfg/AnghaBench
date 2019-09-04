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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_CONTROLLER_DATA ; 
 int /*<<< orphan*/  CARD_CONTROLLER_INDEX ; 
 int CARD_SLOTB ; 
 scalar_t__ CARD_SLOTB_OFFSET ; 
 int /*<<< orphan*/  inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint8_t exca_read_byte(int slot, uint8_t index)
{
	if (slot == CARD_SLOTB)
		index += CARD_SLOTB_OFFSET;

	outb(index, CARD_CONTROLLER_INDEX);
	return inb(CARD_CONTROLLER_DATA);
}