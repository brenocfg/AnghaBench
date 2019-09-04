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

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  current ; 
 unsigned long get_free_page () ; 
 int ind ; 
 int /*<<< orphan*/  map_page (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 

int do_mem_abort(unsigned long addr, unsigned long esr) {
	unsigned long dfs = (esr & 0b111111);
	if ((dfs & 0b111100) == 0b100) {
		unsigned long page = get_free_page();
		if (page == 0) {
			return -1;
		}
		map_page(current, addr & PAGE_MASK, page);
		ind++;
		if (ind > 2){
			return -1;
		}
		return 0;
	}
	return -1;
}