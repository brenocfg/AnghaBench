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
struct snd_emu10k1_fx8010_code {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  name; } ;
struct snd_emu10k1 {TYPE_1__ fx8010; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snd_emu10k1_code_peek (struct snd_emu10k1*,struct snd_emu10k1_fx8010_code*) ; 
 int snd_emu10k1_gpr_peek (struct snd_emu10k1*,struct snd_emu10k1_fx8010_code*) ; 
 int snd_emu10k1_list_controls (struct snd_emu10k1*,struct snd_emu10k1_fx8010_code*) ; 
 int snd_emu10k1_tram_peek (struct snd_emu10k1*,struct snd_emu10k1_fx8010_code*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int snd_emu10k1_icode_peek(struct snd_emu10k1 *emu,
				  struct snd_emu10k1_fx8010_code *icode)
{
	int err;

	mutex_lock(&emu->fx8010.lock);
	strlcpy(icode->name, emu->fx8010.name, sizeof(icode->name));
	/* ok, do the main job */
	err = snd_emu10k1_gpr_peek(emu, icode);
	if (err >= 0)
		err = snd_emu10k1_tram_peek(emu, icode);
	if (err >= 0)
		err = snd_emu10k1_code_peek(emu, icode);
	if (err >= 0)
		err = snd_emu10k1_list_controls(emu, icode);
	mutex_unlock(&emu->fx8010.lock);
	return err;
}