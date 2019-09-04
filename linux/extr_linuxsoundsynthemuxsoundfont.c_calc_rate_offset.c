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
 int /*<<< orphan*/  OFFSET_SAMPLERATE ; 
 int /*<<< orphan*/  SAMPLERATE_RATIO ; 
 int snd_sf_linear_to_log (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
calc_rate_offset(int hz)
{
	return snd_sf_linear_to_log(hz, OFFSET_SAMPLERATE, SAMPLERATE_RATIO);
}