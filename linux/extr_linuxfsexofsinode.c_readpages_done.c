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
struct page_collect {TYPE_1__* sbi; } ;
struct ore_io_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_curr_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  __readpages_done (struct page_collect*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct page_collect*) ; 

__attribute__((used)) static void readpages_done(struct ore_io_state *ios, void *p)
{
	struct page_collect *pcol = p;

	__readpages_done(pcol);
	atomic_dec(&pcol->sbi->s_curr_pending);
	kfree(pcol);
}