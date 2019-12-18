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
struct uniphier_aio_sub {TYPE_1__* cstream; int /*<<< orphan*/  lock; int /*<<< orphan*/  compr_bytes; int /*<<< orphan*/  compr_addr; scalar_t__ threshold; } ;
struct snd_compr_runtime {int fragment_size; } ;
struct TYPE_2__ {struct snd_compr_runtime* runtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  aiodma_rb_clear_irq (struct uniphier_aio_sub*) ; 
 int aiodma_rb_set_threshold (struct uniphier_aio_sub*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  aiodma_rb_sync (struct uniphier_aio_sub*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_compr_fragment_elapsed (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void aiodma_compr_irq(struct uniphier_aio_sub *sub)
{
	struct snd_compr_runtime *runtime = sub->cstream->runtime;
	int bytes = runtime->fragment_size;
	int ret;

	spin_lock(&sub->lock);
	ret = aiodma_rb_set_threshold(sub, sub->compr_bytes,
				      sub->threshold + bytes);
	if (!ret)
		sub->threshold += bytes;

	aiodma_rb_sync(sub, sub->compr_addr, sub->compr_bytes, bytes);
	aiodma_rb_clear_irq(sub);
	spin_unlock(&sub->lock);

	snd_compr_fragment_elapsed(sub->cstream);
}