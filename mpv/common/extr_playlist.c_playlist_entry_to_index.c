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

int playlist_entry_to_index(struct playlist *pl, struct playlist_entry *e)
{
    struct playlist_entry *cur = pl->first;
    int pos = 0;
    if (!e)
        return -1;
    while (cur && cur != e) {
        cur = cur->next;
        pos++;
    }
    return cur == e ? pos : -1;
}