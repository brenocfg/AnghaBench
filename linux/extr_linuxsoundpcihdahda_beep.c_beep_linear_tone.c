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
struct hda_beep {int dummy; } ;

/* Variables and functions */
 int DIGBEEP_HZ_MAX ; 
 int DIGBEEP_HZ_MIN ; 
 int DIGBEEP_HZ_STEP ; 

__attribute__((used)) static int beep_linear_tone(struct hda_beep *beep, int hz)
{
	if (hz <= 0)
		return 0;
	hz *= 1000; /* fixed point */
	hz = hz - DIGBEEP_HZ_MIN
		+ DIGBEEP_HZ_STEP / 2; /* round to nearest step */
	if (hz < 0)
		hz = 0; /* turn off PC beep*/
	else if (hz >= (DIGBEEP_HZ_MAX - DIGBEEP_HZ_MIN))
		hz = 1; /* max frequency */
	else {
		hz /= DIGBEEP_HZ_STEP;
		hz = 255 - hz;
	}
	return hz;
}