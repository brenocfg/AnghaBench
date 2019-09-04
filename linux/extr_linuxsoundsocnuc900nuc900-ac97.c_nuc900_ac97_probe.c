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
struct snd_soc_dai {int dummy; } ;
struct nuc900_audio {scalar_t__ mmio; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 unsigned long ACLINK_EN ; 
 scalar_t__ ACTL_CON ; 
 unsigned long AUDIO_READ (scalar_t__) ; 
 int /*<<< orphan*/  AUDIO_WRITE (scalar_t__,unsigned long) ; 
 unsigned long IIS_AC_PIN_SEL ; 
 int /*<<< orphan*/  ac97_mutex ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nuc900_audio* nuc900_ac97_data ; 

__attribute__((used)) static int nuc900_ac97_probe(struct snd_soc_dai *dai)
{
	struct nuc900_audio *nuc900_audio = nuc900_ac97_data;
	unsigned long val;

	mutex_lock(&ac97_mutex);

	/* enable unit clock */
	clk_enable(nuc900_audio->clk);

	/* enable audio controller and AC-link interface */
	val = AUDIO_READ(nuc900_audio->mmio + ACTL_CON);
	val |= (IIS_AC_PIN_SEL | ACLINK_EN);
	AUDIO_WRITE(nuc900_audio->mmio + ACTL_CON, val);

	mutex_unlock(&ac97_mutex);

	return 0;
}