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
struct snd_pcm {struct rme96* private_data; } ;
struct rme96 {int /*<<< orphan*/ * adat_pcm; } ;

/* Variables and functions */

__attribute__((used)) static void
snd_rme96_free_adat_pcm(struct snd_pcm *pcm)
{
	struct rme96 *rme96 = pcm->private_data;
	rme96->adat_pcm = NULL;
}