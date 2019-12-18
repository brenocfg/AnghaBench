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
struct snd_pcm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_pcm_oss_disconnect_minor (struct snd_pcm*) ; 
 int /*<<< orphan*/  snd_pcm_oss_proc_done (struct snd_pcm*) ; 

__attribute__((used)) static int snd_pcm_oss_unregister_minor(struct snd_pcm *pcm)
{
	snd_pcm_oss_disconnect_minor(pcm);
	snd_pcm_oss_proc_done(pcm);
	return 0;
}