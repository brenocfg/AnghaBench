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
 unsigned int ARRAY_SIZE (unsigned int*) ; 
 unsigned int* rates ; 
 int /*<<< orphan*/  snd_BUG () ; 

__attribute__((used)) static unsigned int snd_cmipci_rate_freq(unsigned int rate)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(rates); i++) {
		if (rates[i] == rate)
			return i;
	}
	snd_BUG();
	return 0;
}