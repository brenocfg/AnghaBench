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

/* Variables and functions */
 int snd_gf1_peek (struct snd_gus_card*,unsigned int) ; 
 int /*<<< orphan*/  snd_gf1_poke (struct snd_gus_card*,unsigned int,unsigned char) ; 

__attribute__((used)) static void snd_interwave_bank_sizes(struct snd_gus_card *gus, int *sizes)
{
	unsigned int idx;
	unsigned int local;
	unsigned char d;

	for (idx = 0; idx < 4; idx++) {
		sizes[idx] = 0;
		d = 0x55;
		for (local = idx << 22;
		     local < (idx << 22) + 0x400000;
		     local += 0x40000, d++) {
			snd_gf1_poke(gus, local, d);
			snd_gf1_poke(gus, local + 1, d + 1);
#if 0
			printk(KERN_DEBUG "d = 0x%x, local = 0x%x, "
			       "local + 1 = 0x%x, idx << 22 = 0x%x\n",
			       d,
			       snd_gf1_peek(gus, local),
			       snd_gf1_peek(gus, local + 1),
			       snd_gf1_peek(gus, idx << 22));
#endif
			if (snd_gf1_peek(gus, local) != d ||
			    snd_gf1_peek(gus, local + 1) != d + 1 ||
			    snd_gf1_peek(gus, idx << 22) != 0x55)
				break;
			sizes[idx]++;
		}
	}
#if 0
	printk(KERN_DEBUG "sizes: %i %i %i %i\n",
	       sizes[0], sizes[1], sizes[2], sizes[3]);
#endif
}