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
struct snd_ml403_ac97cr {int /*<<< orphan*/ * capture_substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WORK_INFO ; 
 struct snd_ml403_ac97cr* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_ml403_ac97cr_capture_close(struct snd_pcm_substream *substream)
{
	struct snd_ml403_ac97cr *ml403_ac97cr;

	ml403_ac97cr = snd_pcm_substream_chip(substream);

	PDEBUG(WORK_INFO, "close(capture)\n");
	ml403_ac97cr->capture_substream = NULL;
	return 0;
}