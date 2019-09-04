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
 int EINVAL ; 
 int /*<<< orphan*/  SB_DT019X_CAPTURE_SW ; 
 unsigned char SB_DT019X_CAP_CD ; 
 unsigned char SB_DT019X_CAP_LINE ; 
 unsigned char SB_DT019X_CAP_MAIN ; 
 unsigned char SB_DT019X_CAP_MIC ; 
 unsigned char SB_DT019X_CAP_SYNTH ; 
 struct snd_sb* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 unsigned char snd_sbmixer_read (struct snd_sb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_sbmixer_write (struct snd_sb*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_dt019x_input_sw_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_sb *sb = snd_kcontrol_chip(kcontrol);
	unsigned long flags;
	int change;
	unsigned char nval, oval;
	
	if (ucontrol->value.enumerated.item[0] > 4)
		return -EINVAL;
	switch (ucontrol->value.enumerated.item[0]) {
	case 0:
		nval = SB_DT019X_CAP_CD;
		break;
	case 1:
		nval = SB_DT019X_CAP_MIC;
		break;
	case 2:
		nval = SB_DT019X_CAP_LINE;
		break;
	case 3:
		nval = SB_DT019X_CAP_SYNTH;
		break;
	case 4:
		nval = SB_DT019X_CAP_MAIN;
		break;
	default:
		nval = SB_DT019X_CAP_MAIN;
	}
	spin_lock_irqsave(&sb->mixer_lock, flags);
	oval = snd_sbmixer_read(sb, SB_DT019X_CAPTURE_SW);
	change = nval != oval;
	if (change)
		snd_sbmixer_write(sb, SB_DT019X_CAPTURE_SW, nval);
	spin_unlock_irqrestore(&sb->mixer_lock, flags);
	return change;
}