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
struct voctrl_playback_state {scalar_t__ paused; int /*<<< orphan*/  percent_pos; int /*<<< orphan*/  taskbar_progress; int /*<<< orphan*/  playing; } ;
struct vo_w32_state {int /*<<< orphan*/  window; int /*<<< orphan*/  taskbar_list3; int /*<<< orphan*/  tbtnCreated; struct voctrl_playback_state current_pstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITaskbarList3_SetProgressState (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITaskbarList3_SetProgressValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TBPF_NOPROGRESS ; 
 int /*<<< orphan*/  TBPF_NORMAL ; 
 int /*<<< orphan*/  TBPF_PAUSED ; 

__attribute__((used)) static void update_playback_state(struct vo_w32_state *w32)
{
    struct voctrl_playback_state *pstate = &w32->current_pstate;

    if (!w32->taskbar_list3 || !w32->tbtnCreated)
        return;

    if (!pstate->playing || !pstate->taskbar_progress) {
        ITaskbarList3_SetProgressState(w32->taskbar_list3, w32->window,
                                       TBPF_NOPROGRESS);
        return;
    }

    ITaskbarList3_SetProgressValue(w32->taskbar_list3, w32->window,
                                   pstate->percent_pos, 100);
    ITaskbarList3_SetProgressState(w32->taskbar_list3, w32->window,
                                   pstate->paused ? TBPF_PAUSED :
                                                    TBPF_NORMAL);
}