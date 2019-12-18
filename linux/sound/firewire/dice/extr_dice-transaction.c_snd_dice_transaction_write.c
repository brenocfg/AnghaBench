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
struct snd_dice {int /*<<< orphan*/  unit; } ;
typedef  enum snd_dice_addr_type { ____Placeholder_snd_dice_addr_type } snd_dice_addr_type ;

/* Variables and functions */
 int /*<<< orphan*/  TCODE_WRITE_BLOCK_REQUEST ; 
 int /*<<< orphan*/  TCODE_WRITE_QUADLET_REQUEST ; 
 int /*<<< orphan*/  get_subaddr (struct snd_dice*,int,unsigned int) ; 
 int snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,unsigned int,int /*<<< orphan*/ ) ; 

int snd_dice_transaction_write(struct snd_dice *dice,
			       enum snd_dice_addr_type type,
			       unsigned int offset, void *buf, unsigned int len)
{
	return snd_fw_transaction(dice->unit,
				  (len == 4) ? TCODE_WRITE_QUADLET_REQUEST :
					       TCODE_WRITE_BLOCK_REQUEST,
				  get_subaddr(dice, type, offset), buf, len, 0);
}