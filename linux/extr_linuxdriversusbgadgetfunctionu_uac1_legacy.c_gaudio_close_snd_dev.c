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
struct gaudio_snd_dev {scalar_t__ filp; } ;
struct gaudio {struct gaudio_snd_dev capture; struct gaudio_snd_dev playback; struct gaudio_snd_dev control; } ;

/* Variables and functions */
 int /*<<< orphan*/  filp_close (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gaudio_close_snd_dev(struct gaudio *gau)
{
	struct gaudio_snd_dev	*snd;

	/* Close control device */
	snd = &gau->control;
	if (snd->filp)
		filp_close(snd->filp, NULL);

	/* Close PCM playback device and setup substream */
	snd = &gau->playback;
	if (snd->filp)
		filp_close(snd->filp, NULL);

	/* Close PCM capture device and setup substream */
	snd = &gau->capture;
	if (snd->filp)
		filp_close(snd->filp, NULL);

	return 0;
}