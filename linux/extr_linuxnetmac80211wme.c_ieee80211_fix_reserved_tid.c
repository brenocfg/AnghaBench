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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static inline u8 ieee80211_fix_reserved_tid(u8 tid)
{
	switch (tid) {
	case 0:
		return 3;
	case 1:
		return 2;
	case 2:
		return 1;
	case 3:
		return 0;
	case 4:
		return 5;
	case 5:
		return 4;
	case 6:
		return 7;
	case 7:
		return 6;
	}

	return 0;
}