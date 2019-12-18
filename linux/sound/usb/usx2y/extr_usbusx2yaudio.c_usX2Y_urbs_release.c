#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_usX2Y_substream {int /*<<< orphan*/ * tmpbuf; TYPE_1__* usX2Y; scalar_t__ urb; int /*<<< orphan*/  endpoint; } ;
struct TYPE_2__ {struct snd_usX2Y_substream** subs; } ;

/* Variables and functions */
 int NRURBS ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_printdd (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usX2Y_urb_release (scalar_t__,int) ; 

__attribute__((used)) static void usX2Y_urbs_release(struct snd_usX2Y_substream *subs)
{
	int i;
	snd_printdd("usX2Y_urbs_release() %i\n", subs->endpoint);
	for (i = 0; i < NRURBS; i++)
		usX2Y_urb_release(subs->urb + i,
				  subs != subs->usX2Y->subs[SNDRV_PCM_STREAM_PLAYBACK]);

	kfree(subs->tmpbuf);
	subs->tmpbuf = NULL;
}