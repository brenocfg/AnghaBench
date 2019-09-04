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
struct hdspm {int system_sample_rate; } ;

/* Variables and functions */

__attribute__((used)) static int hdspm_clock_source(struct hdspm * hdspm)
{
	switch (hdspm->system_sample_rate) {
	case 32000: return 0;
	case 44100: return 1;
	case 48000: return 2;
	case 64000: return 3;
	case 88200: return 4;
	case 96000: return 5;
	case 128000: return 6;
	case 176400: return 7;
	case 192000: return 8;
	}

	return -1;
}