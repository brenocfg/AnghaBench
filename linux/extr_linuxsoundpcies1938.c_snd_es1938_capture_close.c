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
struct es1938 {int /*<<< orphan*/ * capture_substream; } ;

/* Variables and functions */
 struct es1938* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_es1938_capture_close(struct snd_pcm_substream *substream)
{
	struct es1938 *chip = snd_pcm_substream_chip(substream);

	chip->capture_substream = NULL;
	return 0;
}