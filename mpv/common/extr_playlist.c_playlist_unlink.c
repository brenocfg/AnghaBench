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
struct playlist_entry {struct playlist* pl; TYPE_1__* prev; struct playlist_entry* next; } ;
struct playlist {int current_was_replaced; struct playlist_entry* first; TYPE_1__* last; struct playlist_entry* current; } ;
struct TYPE_2__ {struct playlist_entry* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void playlist_unlink(struct playlist *pl, struct playlist_entry *entry)
{
    assert(pl && entry->pl == pl);

    if (pl->current == entry) {
        pl->current = entry->next;
        pl->current_was_replaced = true;
    }

    if (entry->next) {
        entry->next->prev = entry->prev;
    } else {
        pl->last = entry->prev;
    }
    if (entry->prev) {
        entry->prev->next = entry->next;
    } else {
        pl->first = entry->next;
    }
    entry->next = entry->prev = NULL;
    // xxx: we'd want to reset the talloc parent of entry
    entry->pl = NULL;
}