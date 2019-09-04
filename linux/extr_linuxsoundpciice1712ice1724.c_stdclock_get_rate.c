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
 int /*<<< orphan*/  ICEMT1724 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RATE ; 
 int inb (int /*<<< orphan*/ ) ; 
 unsigned int* stdclock_rate_list ; 

__attribute__((used)) static unsigned int stdclock_get_rate(struct snd_ice1712 *ice)
{
	return stdclock_rate_list[inb(ICEMT1724(ice, RATE)) & 15];
}