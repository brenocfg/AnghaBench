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
struct page {int dummy; } ;

/* Variables and functions */
 size_t N_MEMORY ; 
 struct page* new_page_nodemask (struct page*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * node_states ; 
 int page_to_nid (struct page*) ; 

__attribute__((used)) static struct page *new_page(struct page *p, unsigned long private)
{
	int nid = page_to_nid(p);

	return new_page_nodemask(p, nid, &node_states[N_MEMORY]);
}