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
struct snd_soc_dai {int /*<<< orphan*/  component; } ;

/* Variables and functions */
 int _wm8993_set_fll (int /*<<< orphan*/ ,int,int,unsigned int,unsigned int) ; 

__attribute__((used)) static int wm8993_set_fll(struct snd_soc_dai *dai, int fll_id, int source,
			  unsigned int Fref, unsigned int Fout)
{
	return _wm8993_set_fll(dai->component, fll_id, source, Fref, Fout);
}