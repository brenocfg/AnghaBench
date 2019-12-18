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
struct MPContext {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  handle_command_updates (struct MPContext*) ; 
 int /*<<< orphan*/  handle_cursor_autohide (struct MPContext*) ; 
 int /*<<< orphan*/  handle_dummy_ticks (struct MPContext*) ; 
 int /*<<< orphan*/  handle_osd_redraw (struct MPContext*) ; 
 int /*<<< orphan*/  handle_update_cache (struct MPContext*) ; 
 int /*<<< orphan*/  handle_vo_events (struct MPContext*) ; 
 int /*<<< orphan*/  mp_process_input (struct MPContext*) ; 
 int /*<<< orphan*/  mp_wait_events (struct MPContext*) ; 
 int /*<<< orphan*/  update_osd_msg (struct MPContext*) ; 

void mp_idle(struct MPContext *mpctx)
{
    handle_dummy_ticks(mpctx);
    mp_wait_events(mpctx);
    mp_process_input(mpctx);
    handle_command_updates(mpctx);
    handle_update_cache(mpctx);
    handle_cursor_autohide(mpctx);
    handle_vo_events(mpctx);
    update_osd_msg(mpctx);
    handle_osd_redraw(mpctx);
}