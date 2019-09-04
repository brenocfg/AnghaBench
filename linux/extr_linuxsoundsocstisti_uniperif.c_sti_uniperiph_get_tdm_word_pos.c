#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int slot_width; int slots; unsigned int mask; } ;
struct uniperif {TYPE_1__ tdm_slot; } ;

/* Variables and functions */
 int WORD_MAX ; 

int sti_uniperiph_get_tdm_word_pos(struct uniperif *uni,
				   unsigned int *word_pos)
{
	int slot_width = uni->tdm_slot.slot_width / 8;
	int slots_num = uni->tdm_slot.slots;
	unsigned int slots_mask = uni->tdm_slot.mask;
	int i, j, k;
	unsigned int word16_pos[4];

	/* word16_pos:
	 * word16_pos[0] = WORDX_LSB
	 * word16_pos[1] = WORDX_MSB,
	 * word16_pos[2] = WORDX+1_LSB
	 * word16_pos[3] = WORDX+1_MSB
	 */

	/* set unip word position */
	for (i = 0, j = 0, k = 0; (i < slots_num) && (k < WORD_MAX); i++) {
		if ((slots_mask >> i) & 0x01) {
			word16_pos[j] = i * slot_width;

			if (slot_width == 4) {
				word16_pos[j + 1] = word16_pos[j] + 2;
				j++;
			}
			j++;

			if (j > 3) {
				word_pos[k] = word16_pos[1] |
					      (word16_pos[0] << 8) |
					      (word16_pos[3] << 16) |
					      (word16_pos[2] << 24);
				j = 0;
				k++;
			}
		}
	}

	return 0;
}