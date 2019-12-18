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
struct uniphier_aio_sub {int /*<<< orphan*/  pass_through; int /*<<< orphan*/  iec_pc; int /*<<< orphan*/  params; int /*<<< orphan*/  lock; scalar_t__ compr_bytes; scalar_t__ compr_addr; } ;
struct uniphier_aio {struct uniphier_aio_sub* sub; } ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  cpu_dai; } ;
struct snd_compr_stream {size_t direction; struct snd_compr_runtime* runtime; struct snd_soc_pcm_runtime* private_data; } ;
struct snd_compr_runtime {int fragment_size; } ;

/* Variables and functions */
 int aio_if_set_param (struct uniphier_aio_sub*,int /*<<< orphan*/ ) ; 
 int aio_oport_set_stream_type (struct uniphier_aio_sub*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aio_port_set_enable (struct uniphier_aio_sub*,int) ; 
 int aio_port_set_param (struct uniphier_aio_sub*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int aiodma_ch_set_param (struct uniphier_aio_sub*) ; 
 int aiodma_rb_set_buffer (struct uniphier_aio_sub*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct uniphier_aio* uniphier_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uniphier_aio_compr_prepare(struct snd_compr_stream *cstream)
{
	struct snd_soc_pcm_runtime *rtd = cstream->private_data;
	struct snd_compr_runtime *runtime = cstream->runtime;
	struct uniphier_aio *aio = uniphier_priv(rtd->cpu_dai);
	struct uniphier_aio_sub *sub = &aio->sub[cstream->direction];
	int bytes = runtime->fragment_size;
	unsigned long flags;
	int ret;

	ret = aiodma_ch_set_param(sub);
	if (ret)
		return ret;

	spin_lock_irqsave(&sub->lock, flags);
	ret = aiodma_rb_set_buffer(sub, sub->compr_addr,
				   sub->compr_addr + sub->compr_bytes,
				   bytes);
	spin_unlock_irqrestore(&sub->lock, flags);
	if (ret)
		return ret;

	ret = aio_port_set_param(sub, sub->pass_through, &sub->params);
	if (ret)
		return ret;
	ret = aio_oport_set_stream_type(sub, sub->iec_pc);
	if (ret)
		return ret;
	aio_port_set_enable(sub, 1);

	ret = aio_if_set_param(sub, sub->pass_through);
	if (ret)
		return ret;

	return 0;
}