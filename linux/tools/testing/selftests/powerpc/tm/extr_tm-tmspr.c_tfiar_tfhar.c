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
typedef  int /*<<< orphan*/  cpuset ;
typedef  int /*<<< orphan*/  cpu_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPRN_TFHAR ; 
 int /*<<< orphan*/  SPRN_TFIAR ; 
 unsigned long mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,unsigned long) ; 
 int num_loops ; 
 scalar_t__ passed ; 
 int /*<<< orphan*/  sched_setaffinity (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

void tfiar_tfhar(void *in)
{
	int i, cpu;
	unsigned long tfhar, tfhar_rd, tfiar, tfiar_rd;
	cpu_set_t cpuset;

	CPU_ZERO(&cpuset);
	cpu = (unsigned long)in >> 1;
	CPU_SET(cpu, &cpuset);
	sched_setaffinity(0, sizeof(cpuset), &cpuset);

	/* TFIAR: Last bit has to be high so userspace can read register */
	tfiar = ((unsigned long)in) + 1;
	tfiar += 2;
	mtspr(SPRN_TFIAR, tfiar);

	/* TFHAR: Last two bits are reserved */
	tfhar = ((unsigned long)in);
	tfhar &= ~0x3UL;
	tfhar += 4;
	mtspr(SPRN_TFHAR, tfhar);

	for (i = 0; i < num_loops; i++)	{
		tfhar_rd = mfspr(SPRN_TFHAR);
		tfiar_rd = mfspr(SPRN_TFIAR);
		if ( (tfhar != tfhar_rd) || (tfiar != tfiar_rd) ) {
			passed = 0;
			return;
		}
	}
	return;
}