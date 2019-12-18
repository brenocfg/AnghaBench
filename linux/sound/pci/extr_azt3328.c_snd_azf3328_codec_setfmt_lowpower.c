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
struct snd_azf3328_codec_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AZF_FREQ_4000 ; 
 int /*<<< orphan*/  snd_azf3328_codec_setfmt (struct snd_azf3328_codec_data*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline void
snd_azf3328_codec_setfmt_lowpower(struct snd_azf3328_codec_data *codec
)
{
	/* choose lowest frequency for low power consumption.
	 * While this will cause louder noise due to rather coarse frequency,
	 * it should never matter since output should always
	 * get disabled properly when idle anyway. */
	snd_azf3328_codec_setfmt(codec, AZF_FREQ_4000, 8, 1);
}