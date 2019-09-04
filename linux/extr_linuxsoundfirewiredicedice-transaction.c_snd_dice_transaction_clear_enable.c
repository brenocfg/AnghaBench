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
struct snd_dice {int owner_generation; int global_enabled; int /*<<< orphan*/  unit; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int FW_FIXED_GENERATION ; 
 int FW_QUIET ; 
 int /*<<< orphan*/  GLOBAL_ENABLE ; 
 int /*<<< orphan*/  SND_DICE_ADDR_TYPE_GLOBAL ; 
 int /*<<< orphan*/  TCODE_WRITE_QUADLET_REQUEST ; 
 int /*<<< orphan*/  get_subaddr (struct snd_dice*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int,int) ; 

void snd_dice_transaction_clear_enable(struct snd_dice *dice)
{
	__be32 value;

	value = 0;
	snd_fw_transaction(dice->unit, TCODE_WRITE_QUADLET_REQUEST,
			   get_subaddr(dice, SND_DICE_ADDR_TYPE_GLOBAL,
				       GLOBAL_ENABLE),
			   &value, 4, FW_QUIET |
			   FW_FIXED_GENERATION | dice->owner_generation);

	dice->global_enabled = false;
}