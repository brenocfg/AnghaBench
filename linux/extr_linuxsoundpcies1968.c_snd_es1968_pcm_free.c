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
struct snd_pcm {struct es1968* private_data; } ;
struct es1968 {int /*<<< orphan*/ * pcm; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_es1968_free_dmabuf (struct es1968*) ; 

__attribute__((used)) static void snd_es1968_pcm_free(struct snd_pcm *pcm)
{
	struct es1968 *esm = pcm->private_data;
	snd_es1968_free_dmabuf(esm);
	esm->pcm = NULL;
}