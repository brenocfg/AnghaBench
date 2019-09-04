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
struct page_state {int (* action ) (struct page*,unsigned long) ;size_t type; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int MF_DELAYED ; 
 int MF_FAILED ; 
 int MF_RECOVERED ; 
 int /*<<< orphan*/ * action_page_types ; 
 int /*<<< orphan*/  action_result (unsigned long,size_t,int) ; 
 int me_swapcache_dirty (struct page*,unsigned long) ; 
 int page_count (struct page*) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned long,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct page*,unsigned long) ; 

__attribute__((used)) static int page_action(struct page_state *ps, struct page *p,
			unsigned long pfn)
{
	int result;
	int count;

	result = ps->action(p, pfn);

	count = page_count(p) - 1;
	if (ps->action == me_swapcache_dirty && result == MF_DELAYED)
		count--;
	if (count > 0) {
		pr_err("Memory failure: %#lx: %s still referenced by %d users\n",
		       pfn, action_page_types[ps->type], count);
		result = MF_FAILED;
	}
	action_result(pfn, ps->type, result);

	/* Could do more checks here if page looks ok */
	/*
	 * Could adjust zone counters here to correct for the missing page.
	 */

	return (result == MF_RECOVERED || result == MF_DELAYED) ? 0 : -EBUSY;
}