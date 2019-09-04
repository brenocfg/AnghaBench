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
typedef  int u32 ;
struct snd_ac97 {int subsystem_device; scalar_t__ subsystem_vendor; } ;

/* Variables and functions */

__attribute__((used)) static int check_list(struct snd_ac97 *ac97, const unsigned int *list)
{
	u32 subid = ((u32)ac97->subsystem_vendor << 16) | ac97->subsystem_device;
	for (; *list; list++)
		if (*list == subid)
			return 1;
	return 0;
}