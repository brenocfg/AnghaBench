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
struct playlist {int current_was_replaced; int /*<<< orphan*/  current; scalar_t__ first; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  playlist_remove (struct playlist*,scalar_t__) ; 

void playlist_clear(struct playlist *pl)
{
    while (pl->first)
        playlist_remove(pl, pl->first);
    assert(!pl->current);
    pl->current_was_replaced = false;
}