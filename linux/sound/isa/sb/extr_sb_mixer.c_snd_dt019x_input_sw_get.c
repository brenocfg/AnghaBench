#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_sb {int /*<<< orphan*/  mixer_lock; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  SB_DT019X_CAPTURE_SW ; 
#define  SB_DT019X_CAP_CD 131 
#define  SB_DT019X_CAP_LINE 130 
#define  SB_DT019X_CAP_MAIN 129 
#define  SB_DT019X_CAP_MIC 128 
 struct snd_sb* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 unsigned char snd_sbmixer_read (struct snd_sb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_dt019x_input_sw_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_sb *sb = snd_kcontrol_chip(kcontrol);
	unsigned long flags;
	unsigned char oval;
	
	spin_lock_irqsave(&sb->mixer_lock, flags);
	oval = snd_sbmixer_read(sb, SB_DT019X_CAPTURE_SW);
	spin_unlock_irqrestore(&sb->mixer_lock, flags);
	switch (oval & 0x07) {
	case SB_DT019X_CAP_CD:
		ucontrol->value.enumerated.item[0] = 0;
		break;
	case SB_DT019X_CAP_MIC:
		ucontrol->value.enumerated.item[0] = 1;
		break;
	case SB_DT019X_CAP_LINE:
		ucontrol->value.enumerated.item[0] = 2;
		break;
	case SB_DT019X_CAP_MAIN:
		ucontrol->value.enumerated.item[0] = 4;
		break;
	/* To record the synth on these cards you must record the main.   */
	/* Thus SB_DT019X_CAP_SYNTH == SB_DT019X_CAP_MAIN and would cause */
	/* duplicate case labels if left uncommented. */
	/* case SB_DT019X_CAP_SYNTH:
	 *	ucontrol->value.enumerated.item[0] = 3;
	 *	break;
	 */
	default:
		ucontrol->value.enumerated.item[0] = 4;
		break;
	}
	return 0;
}