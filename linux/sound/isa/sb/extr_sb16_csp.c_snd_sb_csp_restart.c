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
struct snd_sb_csp {int running; TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int EBUSY ; 
 int SNDRV_SB_CSP_ST_PAUSED ; 
 int set_codec_parameter (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_sb_csp_restart(struct snd_sb_csp * p)
{
	int result;
	unsigned long flags;

	if (!(p->running & SNDRV_SB_CSP_ST_PAUSED))
		return -EBUSY;

	spin_lock_irqsave(&p->chip->reg_lock, flags);
	result = set_codec_parameter(p->chip, 0x80, 0x00);
	spin_unlock_irqrestore(&p->chip->reg_lock, flags);
	if (!(result))
		p->running &= ~SNDRV_SB_CSP_ST_PAUSED;

	return result;
}