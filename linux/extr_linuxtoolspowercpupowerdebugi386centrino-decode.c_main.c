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

/* Variables and functions */
 unsigned int MCPU ; 
 int /*<<< orphan*/  decode (unsigned int) ; 
 int /*<<< orphan*/  decode_live (unsigned int) ; 
 unsigned int strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int main (int argc, char **argv)
{
	unsigned int cpu, mode = 0;

	if (argc < 2)
		cpu = 0;
	else {
		cpu = strtoul(argv[1], NULL, 0);
		if (cpu >= MCPU)
			mode = 1;
	}

	if (mode)
		decode(cpu);
	else
		decode_live(cpu);

	return 0;
}