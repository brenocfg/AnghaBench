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
struct snd_dice {int global_enabled; int owner_generation; int /*<<< orphan*/  unit; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int FW_FIXED_GENERATION ; 
 int /*<<< orphan*/  GLOBAL_ENABLE ; 
 int /*<<< orphan*/  SND_DICE_ADDR_TYPE_GLOBAL ; 
 int /*<<< orphan*/  TCODE_WRITE_QUADLET_REQUEST ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  get_subaddr (struct snd_dice*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

int snd_dice_transaction_set_enable(struct snd_dice *dice)
{
	__be32 value;
	int err = 0;

	if (dice->global_enabled)
		goto end;

	value = cpu_to_be32(1);
	err = snd_fw_transaction(dice->unit, TCODE_WRITE_QUADLET_REQUEST,
				 get_subaddr(dice, SND_DICE_ADDR_TYPE_GLOBAL,
					     GLOBAL_ENABLE),
				 &value, 4,
				 FW_FIXED_GENERATION | dice->owner_generation);
	if (err < 0)
		goto end;

	dice->global_enabled = true;
end:
	return err;
}