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
typedef  int /*<<< orphan*/  gs_device_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 

void gl_update(gs_device_t *device)
{
	/* does nothing on windows */
	UNUSED_PARAMETER(device);
}