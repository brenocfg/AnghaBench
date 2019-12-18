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
struct snd_compr_tstamp {int copied_total; int byte_offset; } ;
struct snd_compr_stream {struct snd_compr_runtime* runtime; } ;
struct snd_compr_runtime {struct q6asm_dai_rtd* private_data; } ;
struct q6asm_dai_rtd {int copied_total; int pcm_size; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int q6asm_dai_compr_pointer(struct snd_compr_stream *stream,
		struct snd_compr_tstamp *tstamp)
{
	struct snd_compr_runtime *runtime = stream->runtime;
	struct q6asm_dai_rtd *prtd = runtime->private_data;
	unsigned long flags;

	spin_lock_irqsave(&prtd->lock, flags);

	tstamp->copied_total = prtd->copied_total;
	tstamp->byte_offset = prtd->copied_total % prtd->pcm_size;

	spin_unlock_irqrestore(&prtd->lock, flags);

	return 0;
}