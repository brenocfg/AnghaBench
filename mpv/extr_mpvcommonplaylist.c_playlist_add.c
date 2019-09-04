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
struct playlist {int /*<<< orphan*/  last; } ;

/* Variables and functions */
 int /*<<< orphan*/  playlist_insert (struct playlist*,int /*<<< orphan*/ ,struct playlist_entry*) ; 

void playlist_add(struct playlist *pl, struct playlist_entry *add)
{
    playlist_insert(pl, pl->last, add);
}