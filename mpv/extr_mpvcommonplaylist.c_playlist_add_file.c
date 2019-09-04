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
struct playlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  playlist_add (struct playlist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  playlist_entry_new (char const*) ; 

void playlist_add_file(struct playlist *pl, const char *filename)
{
    playlist_add(pl, playlist_entry_new(filename));
}