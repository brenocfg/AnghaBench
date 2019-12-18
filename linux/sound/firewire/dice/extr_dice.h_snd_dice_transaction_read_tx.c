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

/* Variables and functions */
 int /*<<< orphan*/  SND_DICE_ADDR_TYPE_TX ; 
 int snd_dice_transaction_read (struct snd_dice*,int /*<<< orphan*/ ,unsigned int,void*,unsigned int) ; 

__attribute__((used)) static inline int snd_dice_transaction_read_tx(struct snd_dice *dice,
					       unsigned int offset,
					       void *buf, unsigned int len)
{
	return snd_dice_transaction_read(dice, SND_DICE_ADDR_TYPE_TX, offset,
					 buf, len);
}