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
struct metapage {int /*<<< orphan*/  page; scalar_t__ count; scalar_t__ nohomeok; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_metapage (struct metapage*) ; 
 int /*<<< orphan*/  release_metapage (struct metapage*) ; 
 int /*<<< orphan*/  unlock_page (int /*<<< orphan*/ ) ; 

void put_metapage(struct metapage *mp)
{
	if (mp->count || mp->nohomeok) {
		/* Someone else will release this */
		unlock_page(mp->page);
		return;
	}
	get_page(mp->page);
	mp->count++;
	lock_metapage(mp);
	unlock_page(mp->page);
	release_metapage(mp);
}