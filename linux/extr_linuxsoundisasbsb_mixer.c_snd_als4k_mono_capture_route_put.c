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
struct TYPE_4__ {int* item; } ;
struct TYPE_3__ {TYPE_2__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_1__ value; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SB_ALS4000_MONO_IO_CTRL ; 
 struct snd_sb* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 unsigned char snd_sbmixer_read (struct snd_sb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_sbmixer_write (struct snd_sb*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_als4k_mono_capture_route_put(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct snd_sb *sb = snd_kcontrol_chip(kcontrol);
	unsigned long flags;
	int change;
	unsigned char nval, oval;

	if (ucontrol->value.enumerated.item[0] > 2)
		return -EINVAL;
	spin_lock_irqsave(&sb->mixer_lock, flags);
	oval = snd_sbmixer_read(sb, SB_ALS4000_MONO_IO_CTRL);

	nval = (oval & ~(3 << 6))
	     | (ucontrol->value.enumerated.item[0] << 6);
	change = nval != oval;
	if (change)
		snd_sbmixer_write(sb, SB_ALS4000_MONO_IO_CTRL, nval);
	spin_unlock_irqrestore(&sb->mixer_lock, flags);
	return change;
}