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
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen_or_die (char*,char*) ; 
 int fscanf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfx_cur_rc6_ms ; 

int snapshot_gfx_rc6_ms(void)
{
	FILE *fp;
	int retval;

	fp = fopen_or_die("/sys/class/drm/card0/power/rc6_residency_ms", "r");

	retval = fscanf(fp, "%lld", &gfx_cur_rc6_ms);
	if (retval != 1)
		err(1, "GFX rc6");

	fclose(fp);

	return 0;
}