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
struct ichdev {scalar_t__ pcm_open_flag; int /*<<< orphan*/  pcm; } ;

/* Variables and functions */
 struct ichdev* get_ichdev (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_ac97_pcm_close (int /*<<< orphan*/ ) ; 
 int snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_intel8x0_hw_free(struct snd_pcm_substream *substream)
{
	struct ichdev *ichdev = get_ichdev(substream);

	if (ichdev->pcm_open_flag) {
		snd_ac97_pcm_close(ichdev->pcm);
		ichdev->pcm_open_flag = 0;
	}
	return snd_pcm_lib_free_pages(substream);
}