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
struct snd_emu8k_pcm {int* panning; int timer_running; int /*<<< orphan*/  timer_lock; int /*<<< orphan*/  timer; int /*<<< orphan*/  pitch; struct snd_emu8000* emu; } ;
struct snd_emu8000 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMU8000_CPF_WRITE (struct snd_emu8000*,int,int) ; 
 int /*<<< orphan*/  EMU8000_CVCF_WRITE (struct snd_emu8000*,int,int) ; 
 int /*<<< orphan*/  EMU8000_DCYSUSV_WRITE (struct snd_emu8000*,int,int) ; 
 int /*<<< orphan*/  EMU8000_IFATN_WRITE (struct snd_emu8000*,int,int) ; 
 int /*<<< orphan*/  EMU8000_PTRX_WRITE (struct snd_emu8000*,int,unsigned int) ; 
 int /*<<< orphan*/  EMU8000_VTFT_WRITE (struct snd_emu8000*,int,int) ; 
 int calc_pitch_target (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void start_voice(struct snd_emu8k_pcm *rec, int ch)
{
	unsigned long flags;
	struct snd_emu8000 *hw = rec->emu;
	unsigned int temp, aux;
	int pt = calc_pitch_target(rec->pitch);

	/* cutoff and volume */
	EMU8000_IFATN_WRITE(hw, ch, 0xff00);
	EMU8000_VTFT_WRITE(hw, ch, 0xffff);
	EMU8000_CVCF_WRITE(hw, ch, 0xffff);
	/* trigger envelope */
	EMU8000_DCYSUSV_WRITE(hw, ch, 0x7f7f);
	/* set reverb and pitch target */
	temp = 0; // reverb
	if (rec->panning[ch] == 0)
		aux = 0xff;
	else
		aux = (-rec->panning[ch]) & 0xff;
	temp = (temp << 8) | (pt << 16) | aux;
	EMU8000_PTRX_WRITE(hw, ch, temp);
	EMU8000_CPF_WRITE(hw, ch, pt << 16);

	/* start timer */
	spin_lock_irqsave(&rec->timer_lock, flags);
	if (! rec->timer_running) {
		mod_timer(&rec->timer, jiffies + 1);
		rec->timer_running = 1;
	}
	spin_unlock_irqrestore(&rec->timer_lock, flags);
}