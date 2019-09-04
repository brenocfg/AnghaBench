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
struct pagevec {unsigned long nr; int /*<<< orphan*/ * pages; } ;
struct fscache_retrieval {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fscache_mark_page_cached (struct fscache_retrieval*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pagevec_reinit (struct pagevec*) ; 

void fscache_mark_pages_cached(struct fscache_retrieval *op,
			       struct pagevec *pagevec)
{
	unsigned long loop;

	for (loop = 0; loop < pagevec->nr; loop++)
		fscache_mark_page_cached(op, pagevec->pages[loop]);

	pagevec_reinit(pagevec);
}