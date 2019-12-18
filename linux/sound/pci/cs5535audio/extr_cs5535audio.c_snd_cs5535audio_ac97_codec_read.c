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
struct snd_ac97 {struct cs5535audio* private_data; } ;
struct cs5535audio {int dummy; } ;

/* Variables and functions */
 unsigned short snd_cs5535audio_codec_read (struct cs5535audio*,unsigned short) ; 

__attribute__((used)) static unsigned short snd_cs5535audio_ac97_codec_read(struct snd_ac97 *ac97,
						      unsigned short reg)
{
	struct cs5535audio *cs5535au = ac97->private_data;
	return snd_cs5535audio_codec_read(cs5535au, reg);
}