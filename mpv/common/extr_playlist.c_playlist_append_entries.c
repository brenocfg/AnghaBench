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
struct playlist_entry {int dummy; } ;
struct playlist {struct playlist_entry* first; } ;

/* Variables and functions */
 int /*<<< orphan*/  playlist_add (struct playlist*,struct playlist_entry*) ; 
 int /*<<< orphan*/  playlist_unlink (struct playlist*,struct playlist_entry*) ; 

void playlist_append_entries(struct playlist *pl, struct playlist *source_pl)
{
    while (source_pl->first) {
        struct playlist_entry *e = source_pl->first;
        playlist_unlink(source_pl, e);
        playlist_add(pl, e);
    }
}