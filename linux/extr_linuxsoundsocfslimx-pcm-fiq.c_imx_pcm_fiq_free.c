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
 int /*<<< orphan*/  fh ; 
 int /*<<< orphan*/  imx_pcm_free (struct snd_pcm*) ; 
 int /*<<< orphan*/  mxc_set_irq_fiq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_fiq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssi_irq ; 

__attribute__((used)) static void imx_pcm_fiq_free(struct snd_pcm *pcm)
{
	mxc_set_irq_fiq(ssi_irq, 0);
	release_fiq(&fh);
	imx_pcm_free(pcm);
}