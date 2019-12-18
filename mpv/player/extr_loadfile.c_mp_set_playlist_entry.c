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
struct playlist_entry {int dummy; } ;
struct MPContext {scalar_t__ stop_play; TYPE_1__* playlist; } ;
struct TYPE_2__ {int current_was_replaced; struct playlist_entry* current; } ;

/* Variables and functions */
 scalar_t__ PT_CURRENT_ENTRY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mp_wakeup_core (struct MPContext*) ; 
 scalar_t__ playlist_entry_to_index (TYPE_1__*,struct playlist_entry*) ; 

void mp_set_playlist_entry(struct MPContext *mpctx, struct playlist_entry *e)
{
    assert(!e || playlist_entry_to_index(mpctx->playlist, e) >= 0);
    mpctx->playlist->current = e;
    mpctx->playlist->current_was_replaced = false;
    // Make it pick up the new entry.
    if (!mpctx->stop_play)
        mpctx->stop_play = PT_CURRENT_ENTRY;
    mp_wakeup_core(mpctx);
}