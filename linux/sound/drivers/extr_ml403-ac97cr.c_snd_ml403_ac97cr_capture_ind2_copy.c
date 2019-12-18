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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct snd_pcm_indirect2 {int hw_ready; scalar_t__ sw_data; } ;
struct snd_ml403_ac97cr {int /*<<< orphan*/  reg_lock; } ;
struct TYPE_2__ {scalar_t__ dma_area; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_RECDATA (int) ; 
 int CR_RECEMPTY ; 
 int /*<<< orphan*/  CR_REG (struct snd_ml403_ac97cr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RECFIFO ; 
 int /*<<< orphan*/  STATUS ; 
 int in_be32 (int /*<<< orphan*/ ) ; 
 struct snd_ml403_ac97cr* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t
snd_ml403_ac97cr_capture_ind2_copy(struct snd_pcm_substream *substream,
				   struct snd_pcm_indirect2 *rec, size_t bytes)
{
	struct snd_ml403_ac97cr *ml403_ac97cr;
	u16 *dst;
	int copied_words = 0;
	u32 empty = 0;

	ml403_ac97cr = snd_pcm_substream_chip(substream);
	dst = (u16 *)(substream->runtime->dma_area + rec->sw_data);

	spin_lock(&ml403_ac97cr->reg_lock);
	while (((empty = (in_be32(CR_REG(ml403_ac97cr, STATUS)) &
			  CR_RECEMPTY)) != CR_RECEMPTY) && (bytes > 1)) {
		dst[copied_words] = CR_RECDATA(in_be32(CR_REG(ml403_ac97cr,
							      RECFIFO)));
		copied_words++;
		bytes = bytes - 2;
	}
	if (empty != CR_RECEMPTY)
		rec->hw_ready = 1;
	else
		rec->hw_ready = 0;
	spin_unlock(&ml403_ac97cr->reg_lock);

	return (size_t) (copied_words * 2);
}