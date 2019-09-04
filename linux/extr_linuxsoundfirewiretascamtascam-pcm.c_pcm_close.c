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
struct snd_tscm {int dummy; } ;
struct snd_pcm_substream {struct snd_tscm* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_tscm_stream_lock_release (struct snd_tscm*) ; 

__attribute__((used)) static int pcm_close(struct snd_pcm_substream *substream)
{
	struct snd_tscm *tscm = substream->private_data;

	snd_tscm_stream_lock_release(tscm);

	return 0;
}