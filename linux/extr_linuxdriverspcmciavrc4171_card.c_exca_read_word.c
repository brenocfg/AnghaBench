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
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_CONTROLLER_DATA ; 
 int /*<<< orphan*/  CARD_CONTROLLER_INDEX ; 
 int CARD_SLOTB ; 
 scalar_t__ CARD_SLOTB_OFFSET ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint16_t exca_read_word(int slot, uint8_t index)
{
	uint16_t data;

	if (slot == CARD_SLOTB)
		index += CARD_SLOTB_OFFSET;

	outb(index++, CARD_CONTROLLER_INDEX);
	data = inb(CARD_CONTROLLER_DATA);

	outb(index, CARD_CONTROLLER_INDEX);
	data |= ((uint16_t)inb(CARD_CONTROLLER_DATA)) << 8;

	return data;
}