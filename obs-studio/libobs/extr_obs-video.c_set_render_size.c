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
 int /*<<< orphan*/  GS_NEITHER ; 
 int /*<<< orphan*/  gs_enable_depth_test (int) ; 
 int /*<<< orphan*/  gs_ortho (float,float,float,float,float,float) ; 
 int /*<<< orphan*/  gs_set_cull_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_set_viewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void set_render_size(uint32_t width, uint32_t height)
{
	gs_enable_depth_test(false);
	gs_set_cull_mode(GS_NEITHER);

	gs_ortho(0.0f, (float)width, 0.0f, (float)height, -100.0f, 100.0f);
	gs_set_viewport(0, 0, width, height);
}