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
typedef  int /*<<< orphan*/  vortex_t ;

/* Variables and functions */
 int /*<<< orphan*/  vortex_Eqlzr_shutdown (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vortex_eq_free(vortex_t * vortex)
{
	/*
	   //FIXME: segfault because vortex->eqctrl[i] == 4
	   int i;
	   for (i=0; i<10; i++) {
	   if (vortex->eqctrl[i])
	   snd_ctl_remove(vortex->card, vortex->eqctrl[i]);
	   }
	 */
	vortex_Eqlzr_shutdown(vortex);
	return 0;
}