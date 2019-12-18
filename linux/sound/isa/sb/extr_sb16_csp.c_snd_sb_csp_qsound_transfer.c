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
struct snd_sb_csp {int running; int qpos_left; int qpos_right; int /*<<< orphan*/  q_lock; scalar_t__ qpos_changed; int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int ENXIO ; 
 int SNDRV_SB_CSP_ST_QSOUND ; 
 int /*<<< orphan*/  set_codec_parameter (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_sb_csp_qsound_transfer(struct snd_sb_csp * p)
{
	int err = -ENXIO;

	spin_lock(&p->q_lock);
	if (p->running & SNDRV_SB_CSP_ST_QSOUND) {
		set_codec_parameter(p->chip, 0xe0, 0x01);
		/* left channel */
		set_codec_parameter(p->chip, 0x00, p->qpos_left);
		set_codec_parameter(p->chip, 0x02, 0x00);
		/* right channel */
		set_codec_parameter(p->chip, 0x00, p->qpos_right);
		set_codec_parameter(p->chip, 0x03, 0x00);
		err = 0;
	}
	p->qpos_changed = 0;
	spin_unlock(&p->q_lock);
	return err;
}