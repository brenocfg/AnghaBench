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
struct snd_dice {int /*<<< orphan*/  unit; } ;

/* Variables and functions */
 scalar_t__ DICE_PRIVATE_SPACE ; 
 int /*<<< orphan*/  TCODE_READ_BLOCK_REQUEST ; 
 int /*<<< orphan*/  be32_to_cpus (int /*<<< orphan*/ *) ; 
 int snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,void*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dice_proc_read_mem(struct snd_dice *dice, void *buffer,
			      unsigned int offset_q, unsigned int quadlets)
{
	unsigned int i;
	int err;

	err = snd_fw_transaction(dice->unit, TCODE_READ_BLOCK_REQUEST,
				 DICE_PRIVATE_SPACE + 4 * offset_q,
				 buffer, 4 * quadlets, 0);
	if (err < 0)
		return err;

	for (i = 0; i < quadlets; ++i)
		be32_to_cpus(&((u32 *)buffer)[i]);

	return 0;
}