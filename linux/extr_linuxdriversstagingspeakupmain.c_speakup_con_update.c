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
struct vc_data {size_t vc_num; scalar_t__ vc_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 scalar_t__ KD_GRAPHICS ; 
 int /*<<< orphan*/ * speakup_console ; 
 int /*<<< orphan*/  speakup_date (struct vc_data*) ; 
 TYPE_1__ speakup_info ; 
 int /*<<< orphan*/  spin_trylock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ spk_parked ; 
 int spk_paused ; 
 scalar_t__* spk_str_pause ; 
 int /*<<< orphan*/  synth_printf (char*,scalar_t__*) ; 

__attribute__((used)) static void speakup_con_update(struct vc_data *vc)
{
	unsigned long flags;

	if (!speakup_console[vc->vc_num] || spk_parked)
		return;
	if (!spin_trylock_irqsave(&speakup_info.spinlock, flags))
		/* Speakup output, discard */
		return;
	speakup_date(vc);
	if (vc->vc_mode == KD_GRAPHICS && !spk_paused && spk_str_pause[0]) {
		synth_printf("%s", spk_str_pause);
		spk_paused = true;
	}
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
}