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

__attribute__((used)) static inline int HDSPM_bit2freq(int n)
{
	static const int bit2freq_tab[] = {
		0, 32000, 44100, 48000, 64000, 88200,
		96000, 128000, 176400, 192000 };
	if (n < 1 || n > 9)
		return 0;
	return bit2freq_tab[n];
}