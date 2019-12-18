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
typedef  int /*<<< orphan*/  u32 ;
struct uniphier_aio_sub {int rd_total; int /*<<< orphan*/  lock; int /*<<< orphan*/  wr_offs; int /*<<< orphan*/  rd_offs; TYPE_1__* swm; int /*<<< orphan*/  compr_bytes; int /*<<< orphan*/  compr_addr; } ;
struct uniphier_aio {struct uniphier_aio_sub* sub; } ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  cpu_dai; } ;
struct snd_compr_tstamp {int copied_total; int /*<<< orphan*/  byte_offset; } ;
struct snd_compr_stream {size_t direction; struct snd_compr_runtime* runtime; struct snd_soc_pcm_runtime* private_data; } ;
struct snd_compr_runtime {int fragment_size; } ;
struct TYPE_2__ {scalar_t__ dir; } ;

/* Variables and functions */
 scalar_t__ PORT_DIR_OUTPUT ; 
 int /*<<< orphan*/  aiodma_rb_sync (struct uniphier_aio_sub*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct uniphier_aio* uniphier_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uniphier_aio_compr_pointer(struct snd_compr_stream *cstream,
				      struct snd_compr_tstamp *tstamp)
{
	struct snd_soc_pcm_runtime *rtd = cstream->private_data;
	struct snd_compr_runtime *runtime = cstream->runtime;
	struct uniphier_aio *aio = uniphier_priv(rtd->cpu_dai);
	struct uniphier_aio_sub *sub = &aio->sub[cstream->direction];
	int bytes = runtime->fragment_size;
	unsigned long flags;
	u32 pos;

	spin_lock_irqsave(&sub->lock, flags);

	aiodma_rb_sync(sub, sub->compr_addr, sub->compr_bytes, bytes);

	if (sub->swm->dir == PORT_DIR_OUTPUT) {
		pos = sub->rd_offs;
		/* Size of AIO output format is double of IEC61937 */
		tstamp->copied_total = sub->rd_total / 2;
	} else {
		pos = sub->wr_offs;
		tstamp->copied_total = sub->rd_total;
	}
	tstamp->byte_offset = pos;

	spin_unlock_irqrestore(&sub->lock, flags);

	return 0;
}