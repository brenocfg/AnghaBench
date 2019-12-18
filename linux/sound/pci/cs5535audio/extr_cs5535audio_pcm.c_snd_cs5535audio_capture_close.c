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
struct cs5535audio {int /*<<< orphan*/  ac97; } ;

/* Variables and functions */
 int /*<<< orphan*/  olpc_capture_close (int /*<<< orphan*/ ) ; 
 struct cs5535audio* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_cs5535audio_capture_close(struct snd_pcm_substream *substream)
{
	struct cs5535audio *cs5535au = snd_pcm_substream_chip(substream);
	olpc_capture_close(cs5535au->ac97);
	return 0;
}