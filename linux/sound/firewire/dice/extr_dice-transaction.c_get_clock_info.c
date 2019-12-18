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
struct snd_dice {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  GLOBAL_CLOCK_SELECT ; 
 unsigned int snd_dice_transaction_read_global (struct snd_dice*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static unsigned int get_clock_info(struct snd_dice *dice, __be32 *info)
{
	return snd_dice_transaction_read_global(dice, GLOBAL_CLOCK_SELECT,
						info, 4);
}