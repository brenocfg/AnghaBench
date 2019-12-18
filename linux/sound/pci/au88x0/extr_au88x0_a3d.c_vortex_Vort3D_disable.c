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
 int /*<<< orphan*/  vortex_XtalkHw_Disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vortex_a3d_unregister_controls (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vortex_Vort3D_disable(vortex_t * v)
{
	vortex_XtalkHw_Disable(v);
	vortex_a3d_unregister_controls(v);
}