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
struct playlist_entry {struct playlist_entry* next; } ;
struct playlist {struct playlist_entry* first; } ;

/* Variables and functions */

struct playlist_entry *playlist_entry_from_index(struct playlist *pl, int index)
{
    struct playlist_entry *e = pl->first;
    for (int n = 0; ; n++) {
        if (!e || n == index)
            return e;
        e = e->next;
    }
}