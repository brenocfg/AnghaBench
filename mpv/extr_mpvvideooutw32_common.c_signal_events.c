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
struct vo_w32_state {int /*<<< orphan*/  vo; int /*<<< orphan*/  event_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_fetch_or (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vo_wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void signal_events(struct vo_w32_state *w32, int events)
{
    atomic_fetch_or(&w32->event_flags, events);
    vo_wakeup(w32->vo);
}