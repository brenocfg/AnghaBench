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
struct snd_pmac {int /*<<< orphan*/  formats_ok; int /*<<< orphan*/  freqs_ok; } ;
struct snd_pcm_substream {int dummy; } ;
struct pmac_stream {int /*<<< orphan*/  cur_formats; int /*<<< orphan*/  cur_freqs; int /*<<< orphan*/  stream; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  another_stream (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pmac_dma_stop (struct pmac_stream*) ; 
 struct pmac_stream* snd_pmac_get_stream (struct snd_pmac*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_pmac_pcm_close(struct snd_pmac *chip, struct pmac_stream *rec,
			      struct snd_pcm_substream *subs)
{
	struct pmac_stream *astr;

	snd_pmac_dma_stop(rec);

	astr = snd_pmac_get_stream(chip, another_stream(rec->stream));
	if (! astr)
		return -EINVAL;

	/* reset constraints */
	astr->cur_freqs = chip->freqs_ok;
	astr->cur_formats = chip->formats_ok;

	return 0;
}