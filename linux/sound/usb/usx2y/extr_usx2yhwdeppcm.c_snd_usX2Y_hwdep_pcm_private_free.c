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
struct usX2Ydev {int /*<<< orphan*/ * hwdep_pcm_shm; } ;
struct snd_usX2Y_hwdep_pcm_shm {int dummy; } ;
struct snd_hwdep {struct usX2Ydev* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_pages_exact (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void snd_usX2Y_hwdep_pcm_private_free(struct snd_hwdep *hwdep)
{
	struct usX2Ydev *usX2Y = hwdep->private_data;
	if (NULL != usX2Y->hwdep_pcm_shm)
		free_pages_exact(usX2Y->hwdep_pcm_shm, sizeof(struct snd_usX2Y_hwdep_pcm_shm));
}