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
struct snd_pcm_substream {int dummy; } ;
struct snd_ice1712 {int /*<<< orphan*/ * capture_pro_substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRO_RATE_DEFAULT ; 
 scalar_t__ PRO_RATE_RESET ; 
 int /*<<< orphan*/  snd_ice1712_set_pro_rate (struct snd_ice1712*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_ice1712* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_ice1712_capture_pro_close(struct snd_pcm_substream *substream)
{
	struct snd_ice1712 *ice = snd_pcm_substream_chip(substream);

	if (PRO_RATE_RESET)
		snd_ice1712_set_pro_rate(ice, PRO_RATE_DEFAULT, 0);
	ice->capture_pro_substream = NULL;
	return 0;
}