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
struct sync_pair_vid {int /*<<< orphan*/  black; int /*<<< orphan*/  white; int /*<<< orphan*/  tex; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct sync_pair_vid*) ; 
 int /*<<< orphan*/  gs_texture_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 

__attribute__((used)) static void sync_pair_vid_destroy(void *data)
{
	struct sync_pair_vid *spv = data;

	obs_enter_graphics();
	gs_texture_destroy(spv->tex);
	gs_texture_destroy(spv->white);
	gs_texture_destroy(spv->black);
	obs_leave_graphics();

	bfree(spv);
}