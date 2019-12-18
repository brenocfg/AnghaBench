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
struct s3c24xx_audio_simtec_pdata {int /*<<< orphan*/  (* startup ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static int simtec_call_startup(struct s3c24xx_audio_simtec_pdata *pd)
{
	/* call any board supplied startup code, this currently only
	 * covers the bast/vr1000 which have a CPLD in the way of the
	 * LRCLK */
	if (pd->startup)
		pd->startup();

	return 0;
}