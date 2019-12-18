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
 int /*<<< orphan*/  gs_ortho (float,float,float,float,double,float) ; 
 int /*<<< orphan*/  gs_valid (char*) ; 

void gs_set_2d_mode(void)
{
	uint32_t cx, cy;

	if (!gs_valid("gs_set_2d_mode"))
		return;

	gs_get_size(&cx, &cy);
	gs_ortho(0.0f, (float)cx, 0.0f, (float)cy, -1.0, -1024.0f);
}