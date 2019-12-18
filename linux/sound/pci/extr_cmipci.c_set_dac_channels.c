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
struct cmipci_pcm {int fmt; int /*<<< orphan*/  ch; } ;
struct cmipci {int /*<<< orphan*/  reg_lock; scalar_t__ can_multi_ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_CHB3D ; 
 int /*<<< orphan*/  CM_CHB3D5C ; 
 int /*<<< orphan*/  CM_CHB3D6C ; 
 int /*<<< orphan*/  CM_CHB3D8C ; 
 int /*<<< orphan*/  CM_NXCHG ; 
 int /*<<< orphan*/  CM_REG_CHFORMAT ; 
 int /*<<< orphan*/  CM_REG_EXT_MISC ; 
 int /*<<< orphan*/  CM_REG_LEGACY_CTRL ; 
 int /*<<< orphan*/  CM_REG_MISC_CTRL ; 
 int /*<<< orphan*/  CM_XCHGDAC ; 
 int EINVAL ; 
 int /*<<< orphan*/  snd_cmipci_clear_bit (struct cmipci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cmipci_set_bit (struct cmipci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_dac_channels(struct cmipci *cm, struct cmipci_pcm *rec, int channels)
{
	if (channels > 2) {
		if (!cm->can_multi_ch || !rec->ch)
			return -EINVAL;
		if (rec->fmt != 0x03) /* stereo 16bit only */
			return -EINVAL;
	}

	if (cm->can_multi_ch) {
		spin_lock_irq(&cm->reg_lock);
		if (channels > 2) {
			snd_cmipci_set_bit(cm, CM_REG_LEGACY_CTRL, CM_NXCHG);
			snd_cmipci_set_bit(cm, CM_REG_MISC_CTRL, CM_XCHGDAC);
		} else {
			snd_cmipci_clear_bit(cm, CM_REG_LEGACY_CTRL, CM_NXCHG);
			snd_cmipci_clear_bit(cm, CM_REG_MISC_CTRL, CM_XCHGDAC);
		}
		if (channels == 8)
			snd_cmipci_set_bit(cm, CM_REG_EXT_MISC, CM_CHB3D8C);
		else
			snd_cmipci_clear_bit(cm, CM_REG_EXT_MISC, CM_CHB3D8C);
		if (channels == 6) {
			snd_cmipci_set_bit(cm, CM_REG_CHFORMAT, CM_CHB3D5C);
			snd_cmipci_set_bit(cm, CM_REG_LEGACY_CTRL, CM_CHB3D6C);
		} else {
			snd_cmipci_clear_bit(cm, CM_REG_CHFORMAT, CM_CHB3D5C);
			snd_cmipci_clear_bit(cm, CM_REG_LEGACY_CTRL, CM_CHB3D6C);
		}
		if (channels == 4)
			snd_cmipci_set_bit(cm, CM_REG_CHFORMAT, CM_CHB3D);
		else
			snd_cmipci_clear_bit(cm, CM_REG_CHFORMAT, CM_CHB3D);
		spin_unlock_irq(&cm->reg_lock);
	}
	return 0;
}