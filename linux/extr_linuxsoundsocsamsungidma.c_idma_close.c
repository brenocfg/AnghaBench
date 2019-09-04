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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct idma_ctrl* private_data; } ;
struct idma_ctrl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct idma_ctrl*) ; 
 int /*<<< orphan*/  idma_irq ; 
 int /*<<< orphan*/  kfree (struct idma_ctrl*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int idma_close(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct idma_ctrl *prtd = runtime->private_data;

	free_irq(idma_irq, prtd);

	if (!prtd)
		pr_err("idma_close called with prtd == NULL\n");

	kfree(prtd);

	return 0;
}