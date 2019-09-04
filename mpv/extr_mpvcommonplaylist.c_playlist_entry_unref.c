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
struct playlist_entry {scalar_t__ reserved; } ;

/* Variables and functions */
 int /*<<< orphan*/  talloc_free (struct playlist_entry*) ; 

void playlist_entry_unref(struct playlist_entry *e)
{
    e->reserved--;
    if (e->reserved < 0)
        talloc_free(e);
}