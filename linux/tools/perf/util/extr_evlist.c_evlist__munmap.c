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
struct evlist {int /*<<< orphan*/  overwrite_mmap; int /*<<< orphan*/  mmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  evlist__munmap_nofree (struct evlist*) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

void evlist__munmap(struct evlist *evlist)
{
	evlist__munmap_nofree(evlist);
	zfree(&evlist->mmap);
	zfree(&evlist->overwrite_mmap);
}