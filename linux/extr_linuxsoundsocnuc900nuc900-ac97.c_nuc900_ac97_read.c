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
struct snd_ac97 {int dummy; } ;
struct nuc900_audio {scalar_t__ mmio; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ACTL_ACCON ; 
 scalar_t__ ACTL_ACIS1 ; 
 scalar_t__ ACTL_ACIS2 ; 
 scalar_t__ ACTL_ACOS0 ; 
 scalar_t__ ACTL_ACOS1 ; 
 int AC_R_FINISH ; 
 int AUDIO_READ (scalar_t__) ; 
 int /*<<< orphan*/  AUDIO_WRITE (scalar_t__,unsigned long) ; 
 unsigned long EPERM ; 
 unsigned short R_WB ; 
 unsigned long SLOT1_VALID ; 
 unsigned long VALID_FRAME ; 
 int /*<<< orphan*/  ac97_mutex ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nuc900_audio* nuc900_ac97_data ; 
 unsigned long nuc900_checkready () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static unsigned short nuc900_ac97_read(struct snd_ac97 *ac97,
					unsigned short reg)
{
	struct nuc900_audio *nuc900_audio = nuc900_ac97_data;
	unsigned long timeout = 0x10000, val;

	mutex_lock(&ac97_mutex);

	val = nuc900_checkready();
	if (val) {
		dev_err(nuc900_audio->dev, "AC97 codec is not ready\n");
		goto out;
	}

	/* set the R_WB bit and write register index */
	AUDIO_WRITE(nuc900_audio->mmio + ACTL_ACOS1, R_WB | reg);

	/* set the valid frame bit and valid slots */
	val = AUDIO_READ(nuc900_audio->mmio + ACTL_ACOS0);
	val |= (VALID_FRAME | SLOT1_VALID);
	AUDIO_WRITE(nuc900_audio->mmio + ACTL_ACOS0, val);

	udelay(100);

	/* polling the AC_R_FINISH */
	while (!(AUDIO_READ(nuc900_audio->mmio + ACTL_ACCON) & AC_R_FINISH)
								&& --timeout)
		mdelay(1);

	if (!timeout) {
		dev_err(nuc900_audio->dev, "AC97 read register time out !\n");
		val = -EPERM;
		goto out;
	}

	val = AUDIO_READ(nuc900_audio->mmio + ACTL_ACOS0) ;
	val &= ~SLOT1_VALID;
	AUDIO_WRITE(nuc900_audio->mmio + ACTL_ACOS0, val);

	if (AUDIO_READ(nuc900_audio->mmio + ACTL_ACIS1) >> 2 != reg) {
		dev_err(nuc900_audio->dev,
				"R_INDEX of REG_ACTL_ACIS1 not match!\n");
	}

	udelay(100);
	val = (AUDIO_READ(nuc900_audio->mmio + ACTL_ACIS2) & 0xFFFF);

out:
	mutex_unlock(&ac97_mutex);
	return val;
}