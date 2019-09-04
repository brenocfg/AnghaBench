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
struct playlist_entry {int removed; } ;
struct playlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  playlist_entry_unref (struct playlist_entry*) ; 
 int /*<<< orphan*/  playlist_unlink (struct playlist*,struct playlist_entry*) ; 

void playlist_remove(struct playlist *pl, struct playlist_entry *entry)
{
    playlist_unlink(pl, entry);
    entry->removed = true;
    playlist_entry_unref(entry);
}