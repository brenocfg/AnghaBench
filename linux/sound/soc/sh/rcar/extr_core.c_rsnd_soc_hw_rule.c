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
struct snd_interval {void* max; void* min; } ;
struct rsnd_dai {int dummy; } ;

/* Variables and functions */
 void* UINT_MAX ; 
 void* max (void*,unsigned int) ; 
 void* min (void*,unsigned int) ; 
 unsigned int rsnd_ssi_clk_query (struct rsnd_dai*,void*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_interval_any (struct snd_interval*) ; 
 int snd_interval_refine (struct snd_interval*,struct snd_interval*) ; 
 int /*<<< orphan*/  snd_interval_test (struct snd_interval*,unsigned int) ; 

__attribute__((used)) static int rsnd_soc_hw_rule(struct rsnd_dai *rdai,
			    unsigned int *list, int list_num,
			    struct snd_interval *baseline, struct snd_interval *iv)
{
	struct snd_interval p;
	unsigned int rate;
	int i;

	snd_interval_any(&p);
	p.min = UINT_MAX;
	p.max = 0;

	for (i = 0; i < list_num; i++) {

		if (!snd_interval_test(iv, list[i]))
			continue;

		rate = rsnd_ssi_clk_query(rdai,
					  baseline->min, list[i], NULL);
		if (rate > 0) {
			p.min = min(p.min, list[i]);
			p.max = max(p.max, list[i]);
		}

		rate = rsnd_ssi_clk_query(rdai,
					  baseline->max, list[i], NULL);
		if (rate > 0) {
			p.min = min(p.min, list[i]);
			p.max = max(p.max, list[i]);
		}
	}

	return snd_interval_refine(iv, &p);
}