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
typedef  scalar_t__ u64 ;
struct snd_dice {int /*<<< orphan*/  unit; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 scalar_t__ DICE_EXT_APP_SPACE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TCODE_READ_BLOCK_REQUEST ; 
 int be32_to_cpu (scalar_t__) ; 
 int detect_stream_formats (struct snd_dice*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int,int /*<<< orphan*/ ) ; 

int snd_dice_detect_extension_formats(struct snd_dice *dice)
{
	__be32 *pointers;
	unsigned int i;
	u64 section_addr;
	int err;

	pointers = kmalloc_array(9, sizeof(__be32) * 2, GFP_KERNEL);
	if (pointers == NULL)
		return -ENOMEM;

	err = snd_fw_transaction(dice->unit, TCODE_READ_BLOCK_REQUEST,
				 DICE_EXT_APP_SPACE, pointers,
				 9 * sizeof(__be32) * 2, 0);
	if (err < 0)
		goto end;

	/* Check two of them for offset have the same value or not. */
	for (i = 0; i < 9; ++i) {
		int j;

		for (j = i + 1; j < 9; ++j) {
			if (pointers[i * 2] == pointers[j * 2])
				goto end;
		}
	}

	section_addr = DICE_EXT_APP_SPACE + be32_to_cpu(pointers[12]) * 4;
	err = detect_stream_formats(dice, section_addr);
end:
	kfree(pointers);
	return err;
}