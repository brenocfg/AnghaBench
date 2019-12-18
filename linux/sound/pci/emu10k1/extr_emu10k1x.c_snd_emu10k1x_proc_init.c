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
struct emu10k1x {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_card_rw_proc_new (int /*<<< orphan*/ ,char*,struct emu10k1x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu10k1x_proc_reg_read ; 
 int /*<<< orphan*/  snd_emu10k1x_proc_reg_write ; 

__attribute__((used)) static int snd_emu10k1x_proc_init(struct emu10k1x *emu)
{
	snd_card_rw_proc_new(emu->card, "emu10k1x_regs", emu,
			     snd_emu10k1x_proc_reg_read,
			     snd_emu10k1x_proc_reg_write);
	return 0;
}