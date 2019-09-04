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
 unsigned short WM_VOL_MAX ; 
 unsigned short WM_VOL_MUTE ; 
 int /*<<< orphan*/  wm_put (struct snd_ice1712*,unsigned int,unsigned char) ; 
 int /*<<< orphan*/  wm_put_nocache (struct snd_ice1712*,unsigned int,int) ; 
 int* wm_vol ; 

__attribute__((used)) static void wm_set_vol(struct snd_ice1712 *ice, unsigned int index,
			unsigned short vol, unsigned short master)
{
	unsigned char nvol;

	if ((master & WM_VOL_MUTE) || (vol & WM_VOL_MUTE))
		nvol = 0;
	else
		nvol = 127 - wm_vol[(((vol & ~WM_VOL_MUTE) *
			(master & ~WM_VOL_MUTE)) / 127) & WM_VOL_MAX];

	wm_put(ice, index, nvol);
	wm_put_nocache(ice, index, 0x180 | nvol);
}