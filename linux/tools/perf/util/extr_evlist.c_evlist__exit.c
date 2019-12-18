#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  pollfd; } ;
struct evlist {TYPE_1__ core; int /*<<< orphan*/  overwrite_mmap; int /*<<< orphan*/  mmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  fdarray__exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

void evlist__exit(struct evlist *evlist)
{
	zfree(&evlist->mmap);
	zfree(&evlist->overwrite_mmap);
	fdarray__exit(&evlist->core.pollfd);
}