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

__attribute__((used)) static int playlist_count(struct playlist *pl)
{
    int c = 0;
    for (struct playlist_entry *e = pl->first; e; e = e->next)
        c++;
    return c;
}