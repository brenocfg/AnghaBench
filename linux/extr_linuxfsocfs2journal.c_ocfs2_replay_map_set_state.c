#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_super {TYPE_1__* replay_map; } ;
struct TYPE_2__ {int rm_state; } ;

/* Variables and functions */
 int REPLAY_DONE ; 

__attribute__((used)) static void ocfs2_replay_map_set_state(struct ocfs2_super *osb, int state)
{
	if (!osb->replay_map)
		return;

	/* If we've already queued the replay, we don't have any more to do */
	if (osb->replay_map->rm_state == REPLAY_DONE)
		return;

	osb->replay_map->rm_state = state;
}