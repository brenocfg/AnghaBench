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
struct snd_pcm_substream {struct snd_efw* private_data; } ;
struct snd_efw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_efw_stream_lock_release (struct snd_efw*) ; 

__attribute__((used)) static int pcm_close(struct snd_pcm_substream *substream)
{
	struct snd_efw *efw = substream->private_data;
	snd_efw_stream_lock_release(efw);
	return 0;
}