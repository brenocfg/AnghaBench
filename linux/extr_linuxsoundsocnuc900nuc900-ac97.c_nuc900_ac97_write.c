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
 scalar_t__ ACTL_ACOS0 ; 
 scalar_t__ ACTL_ACOS1 ; 
 scalar_t__ ACTL_ACOS2 ; 
 unsigned long AC_W_FINISH ; 
 unsigned long AUDIO_READ (scalar_t__) ; 
 int /*<<< orphan*/  AUDIO_WRITE (scalar_t__,unsigned long) ; 
 unsigned long SLOT1_VALID ; 
 unsigned long SLOT2_VALID ; 
 unsigned long VALID_FRAME ; 
 int /*<<< orphan*/  ac97_mutex ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nuc900_audio* nuc900_ac97_data ; 
 unsigned long nuc900_checkready () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void nuc900_ac97_write(struct snd_ac97 *ac97, unsigned short reg,
				unsigned short val)
{
	struct nuc900_audio *nuc900_audio = nuc900_ac97_data;
	unsigned long tmp, timeout = 0x10000;

	mutex_lock(&ac97_mutex);

	tmp = nuc900_checkready();
	if (tmp)
		dev_err(nuc900_audio->dev, "AC97 codec is not ready\n");

	/* clear the R_WB bit and write register index */
	AUDIO_WRITE(nuc900_audio->mmio + ACTL_ACOS1, reg);

	/* write register value */
	AUDIO_WRITE(nuc900_audio->mmio + ACTL_ACOS2, val);

	/* set the valid frame bit and valid slots */
	tmp = AUDIO_READ(nuc900_audio->mmio + ACTL_ACOS0);
	tmp |= SLOT1_VALID | SLOT2_VALID | VALID_FRAME;
	AUDIO_WRITE(nuc900_audio->mmio + ACTL_ACOS0, tmp);

	udelay(100);

	/* polling the AC_W_FINISH */
	while ((AUDIO_READ(nuc900_audio->mmio + ACTL_ACCON) & AC_W_FINISH)
								&& --timeout)
		mdelay(1);

	if (!timeout)
		dev_err(nuc900_audio->dev, "AC97 write register time out !\n");

	tmp = AUDIO_READ(nuc900_audio->mmio + ACTL_ACOS0);
	tmp &= ~(SLOT1_VALID | SLOT2_VALID);
	AUDIO_WRITE(nuc900_audio->mmio + ACTL_ACOS0, tmp);

	mutex_unlock(&ac97_mutex);

}