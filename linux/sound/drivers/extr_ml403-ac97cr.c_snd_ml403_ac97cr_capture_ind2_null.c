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
typedef  int u32 ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_indirect2 {scalar_t__ hw_ready; } ;
struct snd_ml403_ac97cr {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int CR_RECDATA (int) ; 
 int CR_RECEMPTY ; 
 int /*<<< orphan*/  CR_REG (struct snd_ml403_ac97cr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RECFIFO ; 
 int /*<<< orphan*/  STATUS ; 
 int in_be32 (int /*<<< orphan*/ ) ; 
 struct snd_ml403_ac97cr* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t
snd_ml403_ac97cr_capture_ind2_null(struct snd_pcm_substream *substream,
				   struct snd_pcm_indirect2 *rec)
{
	struct snd_ml403_ac97cr *ml403_ac97cr;
	int copied_words = 0;
	u32 empty = 0;

	ml403_ac97cr = snd_pcm_substream_chip(substream);

	spin_lock(&ml403_ac97cr->reg_lock);
	while ((empty = (in_be32(CR_REG(ml403_ac97cr, STATUS)) &
			 CR_RECEMPTY)) != CR_RECEMPTY) {
		volatile u32 trash;

		trash = CR_RECDATA(in_be32(CR_REG(ml403_ac97cr, RECFIFO)));
		/* Hmmmm, really necessary? Don't want call to in_be32()
		 * to be optimised away!
		 */
		trash++;
		copied_words++;
	}
	rec->hw_ready = 0;
	spin_unlock(&ml403_ac97cr->reg_lock);

	return (size_t) (copied_words * 2);
}