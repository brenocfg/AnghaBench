#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stats_state {int dummy; } ;
struct stats {int dummy; } ;
struct TYPE_4__ {int accepting_conns; } ;

/* Variables and functions */
 scalar_t__ ITEM_UPDATE_INTERVAL ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ process_started ; 
 TYPE_1__ stats ; 
 int /*<<< orphan*/  stats_prefix_init () ; 
 TYPE_1__ stats_state ; 
 scalar_t__ time (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stats_init(void) {
    memset(&stats, 0, sizeof(struct stats));
    memset(&stats_state, 0, sizeof(struct stats_state));
    stats_state.accepting_conns = true; /* assuming we start in this state. */

    /* make the time we started always be 2 seconds before we really
       did, so time(0) - time.started is never zero.  if so, things
       like 'settings.oldest_live' which act as booleans as well as
       values are now false in boolean context... */
    process_started = time(0) - ITEM_UPDATE_INTERVAL - 2;
    stats_prefix_init();
}