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
struct nuc900_audio {int /*<<< orphan*/  dev; scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ ACTL_ACCON ; 
 unsigned long AC_W_RES ; 
 unsigned long AUDIO_READ (scalar_t__) ; 
 int /*<<< orphan*/  AUDIO_WRITE (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  ac97_mutex ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nuc900_audio* nuc900_ac97_data ; 
 unsigned long nuc900_checkready () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void nuc900_ac97_warm_reset(struct snd_ac97 *ac97)
{
	struct nuc900_audio *nuc900_audio = nuc900_ac97_data;
	unsigned long val;

	mutex_lock(&ac97_mutex);

	/* warm reset AC 97 */
	val = AUDIO_READ(nuc900_audio->mmio + ACTL_ACCON);
	val |= AC_W_RES;
	AUDIO_WRITE(nuc900_audio->mmio + ACTL_ACCON, val);

	udelay(100);

	val = nuc900_checkready();
	if (val)
		dev_err(nuc900_audio->dev, "AC97 codec is not ready\n");

	mutex_unlock(&ac97_mutex);
}