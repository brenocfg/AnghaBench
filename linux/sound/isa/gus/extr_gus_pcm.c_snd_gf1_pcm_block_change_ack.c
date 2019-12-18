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
struct snd_gus_card {int dummy; } ;
struct gus_pcm_private {int /*<<< orphan*/  sleep; int /*<<< orphan*/  dma_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_gf1_pcm_block_change_ack(struct snd_gus_card * gus, void *private_data)
{
	struct gus_pcm_private *pcmp = private_data;

	if (pcmp) {
		atomic_dec(&pcmp->dma_count);
		wake_up(&pcmp->sleep);
	}
}