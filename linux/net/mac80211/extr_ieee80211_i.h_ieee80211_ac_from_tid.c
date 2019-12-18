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
 int* ieee802_1d_to_ac ; 

__attribute__((used)) static inline int ieee80211_ac_from_tid(int tid)
{
	return ieee802_1d_to_ac[tid & 7];
}