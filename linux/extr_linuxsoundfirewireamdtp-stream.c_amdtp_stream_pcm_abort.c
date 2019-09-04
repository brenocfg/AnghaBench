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
struct amdtp_stream {int /*<<< orphan*/  pcm; } ;

/* Variables and functions */
 struct snd_pcm_substream* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_stop_xrun (struct snd_pcm_substream*) ; 

void amdtp_stream_pcm_abort(struct amdtp_stream *s)
{
	struct snd_pcm_substream *pcm;

	pcm = READ_ONCE(s->pcm);
	if (pcm)
		snd_pcm_stop_xrun(pcm);
}