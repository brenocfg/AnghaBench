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
struct vo_w32_state {int /*<<< orphan*/  window; } ;

/* Variables and functions */
 scalar_t__ GetCurrentThreadId () ; 
 scalar_t__ GetWindowThreadProcessId (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PostMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendNotifyMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_NULL ; 

__attribute__((used)) static void wakeup_gui_thread(void *ctx)
{
    struct vo_w32_state *w32 = ctx;
    // Wake up the window procedure (which processes the dispatch queue)
    if (GetWindowThreadProcessId(w32->window, NULL) == GetCurrentThreadId()) {
        PostMessageW(w32->window, WM_NULL, 0, 0);
    } else {
        // Use a sent message when cross-thread, since the queue of sent
        // messages is processed in some cases when posted messages are blocked
        SendNotifyMessageW(w32->window, WM_NULL, 0, 0);
    }
}