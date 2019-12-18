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
struct snd_ps3_card_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PS3_AUDIO_KICK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PS3_AUDIO_KICK_REQUEST ; 
 int /*<<< orphan*/  update_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void snd_ps3_kick_dma(struct snd_ps3_card_info *card)
{

	update_reg(PS3_AUDIO_KICK(0), PS3_AUDIO_KICK_REQUEST);
	/* ensure the hardware sees the change */
	wmb();
}