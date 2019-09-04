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
typedef  int u8 ;
struct cs5535audio {int /*<<< orphan*/  capture_substream; int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACC_BM1_STATUS ; 
 int EOP ; 
 int cs_readb (struct cs5535audio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void process_bm1_irq(struct cs5535audio *cs5535au)
{
	u8 bm_stat;
	spin_lock(&cs5535au->reg_lock);
	bm_stat = cs_readb(cs5535au, ACC_BM1_STATUS);
	spin_unlock(&cs5535au->reg_lock);
	if (bm_stat & EOP)
		snd_pcm_period_elapsed(cs5535au->capture_substream);
}