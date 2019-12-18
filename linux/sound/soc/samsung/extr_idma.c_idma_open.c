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
struct idma_ctrl {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  idma_hardware ; 
 int /*<<< orphan*/  idma_irq ; 
 int /*<<< orphan*/  iis_irq ; 
 int /*<<< orphan*/  kfree (struct idma_ctrl*) ; 
 struct idma_ctrl* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct idma_ctrl*) ; 
 int /*<<< orphan*/  snd_soc_set_runtime_hwparams (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int idma_open(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct idma_ctrl *prtd;
	int ret;

	snd_soc_set_runtime_hwparams(substream, &idma_hardware);

	prtd = kzalloc(sizeof(struct idma_ctrl), GFP_KERNEL);
	if (prtd == NULL)
		return -ENOMEM;

	ret = request_irq(idma_irq, iis_irq, 0, "i2s", prtd);
	if (ret < 0) {
		pr_err("fail to claim i2s irq , ret = %d\n", ret);
		kfree(prtd);
		return ret;
	}

	spin_lock_init(&prtd->lock);

	runtime->private_data = prtd;

	return 0;
}