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

__attribute__((used)) static inline int emu10k1_ccis(int stereo, int w_16)
{
	if (w_16) {
		return stereo ? 24 : 26;
	} else {
		return stereo ? 24*2 : 26*2;
	}
}