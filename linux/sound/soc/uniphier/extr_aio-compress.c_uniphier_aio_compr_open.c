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
struct uniphier_aio_sub {int pass_through; int use_mmap; struct snd_compr_stream* cstream; } ;
struct uniphier_aio {struct uniphier_aio_sub* sub; } ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  cpu_dai; } ;
struct snd_compr_stream {size_t direction; struct snd_soc_pcm_runtime* private_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int aio_init (struct uniphier_aio_sub*) ; 
 int uniphier_aio_comprdma_new (struct snd_soc_pcm_runtime*) ; 
 struct uniphier_aio* uniphier_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uniphier_aio_compr_open(struct snd_compr_stream *cstream)
{
	struct snd_soc_pcm_runtime *rtd = cstream->private_data;
	struct uniphier_aio *aio = uniphier_priv(rtd->cpu_dai);
	struct uniphier_aio_sub *sub = &aio->sub[cstream->direction];
	int ret;

	if (sub->cstream)
		return -EBUSY;

	sub->cstream = cstream;
	sub->pass_through = 1;
	sub->use_mmap = false;

	ret = uniphier_aio_comprdma_new(rtd);
	if (ret)
		return ret;

	ret = aio_init(sub);
	if (ret)
		return ret;

	return 0;
}