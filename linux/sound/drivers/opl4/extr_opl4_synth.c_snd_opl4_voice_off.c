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
struct snd_opl4 {int /*<<< orphan*/  off_voices; } ;
struct opl4_voice {int /*<<< orphan*/  reg_misc; scalar_t__ number; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPL4_KEY_ON_BIT ; 
 scalar_t__ OPL4_REG_MISC ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_opl4_write (struct snd_opl4*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_opl4_voice_off(struct snd_opl4 *opl4, struct opl4_voice *voice)
{
	list_move_tail(&voice->list, &opl4->off_voices);

	voice->reg_misc &= ~OPL4_KEY_ON_BIT;
	snd_opl4_write(opl4, OPL4_REG_MISC + voice->number, voice->reg_misc);
}