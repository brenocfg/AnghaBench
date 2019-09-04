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
struct snd_ice1712 {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned int*) ; 
 int /*<<< orphan*/  ICEMT1724 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RATE ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 unsigned int* stdclock_rate_list ; 

__attribute__((used)) static void stdclock_set_rate(struct snd_ice1712 *ice, unsigned int rate)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(stdclock_rate_list); i++) {
		if (stdclock_rate_list[i] == rate) {
			outb(i, ICEMT1724(ice, RATE));
			return;
		}
	}
}