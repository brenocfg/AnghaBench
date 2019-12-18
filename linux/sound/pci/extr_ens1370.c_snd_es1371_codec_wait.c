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

/* Variables and functions */
 int /*<<< orphan*/  AC97_RESET ; 
 int /*<<< orphan*/  AC97_VENDOR_ID1 ; 
 int /*<<< orphan*/  AC97_VENDOR_ID2 ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  snd_es1371_codec_read (struct snd_ac97*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_es1371_codec_wait(struct snd_ac97 *ac97)
{
	msleep(750);
	snd_es1371_codec_read(ac97, AC97_RESET);
	snd_es1371_codec_read(ac97, AC97_VENDOR_ID1);
	snd_es1371_codec_read(ac97, AC97_VENDOR_ID2);
	msleep(50);
}