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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen_or_die (char*,char*) ; 
 int fscanf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfx_cur_mhz ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 

int snapshot_gfx_mhz(void)
{
	static FILE *fp;
	int retval;

	if (fp == NULL)
		fp = fopen_or_die("/sys/class/graphics/fb0/device/drm/card0/gt_cur_freq_mhz", "r");
	else {
		rewind(fp);
		fflush(fp);
	}

	retval = fscanf(fp, "%d", &gfx_cur_mhz);
	if (retval != 1)
		err(1, "GFX MHz");

	return 0;
}