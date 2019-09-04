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
struct nuc900_audio {scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ ACTL_ACCON ; 
 scalar_t__ ACTL_RESET ; 
 unsigned long ACTL_RESET_BIT ; 
 unsigned long AC_C_RES ; 
 unsigned long AC_RESET ; 
 unsigned long AUDIO_READ (scalar_t__) ; 
 int /*<<< orphan*/  AUDIO_WRITE (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  ac97_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nuc900_audio* nuc900_ac97_data ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void nuc900_ac97_cold_reset(struct snd_ac97 *ac97)
{
	struct nuc900_audio *nuc900_audio = nuc900_ac97_data;
	unsigned long val;

	mutex_lock(&ac97_mutex);

	/* reset Audio Controller */
	val = AUDIO_READ(nuc900_audio->mmio + ACTL_RESET);
	val |= ACTL_RESET_BIT;
	AUDIO_WRITE(nuc900_audio->mmio + ACTL_RESET, val);

	val = AUDIO_READ(nuc900_audio->mmio + ACTL_RESET);
	val &= (~ACTL_RESET_BIT);
	AUDIO_WRITE(nuc900_audio->mmio + ACTL_RESET, val);

	/* reset AC-link interface */

	val = AUDIO_READ(nuc900_audio->mmio + ACTL_RESET);
	val |= AC_RESET;
	AUDIO_WRITE(nuc900_audio->mmio + ACTL_RESET, val);

	val = AUDIO_READ(nuc900_audio->mmio + ACTL_RESET);
	val &= ~AC_RESET;
	AUDIO_WRITE(nuc900_audio->mmio + ACTL_RESET, val);

	/* cold reset AC 97 */
	val = AUDIO_READ(nuc900_audio->mmio + ACTL_ACCON);
	val |= AC_C_RES;
	AUDIO_WRITE(nuc900_audio->mmio + ACTL_ACCON, val);

	val = AUDIO_READ(nuc900_audio->mmio + ACTL_ACCON);
	val &= (~AC_C_RES);
	AUDIO_WRITE(nuc900_audio->mmio + ACTL_ACCON, val);

	udelay(100);

	mutex_unlock(&ac97_mutex);

}