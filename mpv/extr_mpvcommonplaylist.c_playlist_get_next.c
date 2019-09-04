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
struct playlist_entry {struct playlist_entry* next; struct playlist_entry* prev; struct playlist* pl; } ;
struct playlist {struct playlist_entry* current; scalar_t__ current_was_replaced; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

struct playlist_entry *playlist_get_next(struct playlist *pl, int direction)
{
    assert(direction == -1 || direction == +1);
    if (!pl->current)
        return NULL;
    assert(pl->current->pl == pl);
    if (direction < 0)
        return pl->current->prev;
    return pl->current_was_replaced ? pl->current : pl->current->next;
}