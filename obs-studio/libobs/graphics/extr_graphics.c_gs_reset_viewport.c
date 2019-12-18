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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  gs_get_size (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  gs_set_viewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gs_valid (char*) ; 

void gs_reset_viewport(void)
{
	uint32_t cx, cy;

	if (!gs_valid("gs_reset_viewport"))
		return;

	gs_get_size(&cx, &cy);
	gs_set_viewport(0, 0, (int)cx, (int)cy);
}