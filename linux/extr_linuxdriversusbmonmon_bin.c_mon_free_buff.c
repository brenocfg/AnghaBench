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
struct mon_pgmap {scalar_t__ ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_page (unsigned long) ; 

__attribute__((used)) static void mon_free_buff(struct mon_pgmap *map, int npages)
{
	int n;

	for (n = 0; n < npages; n++)
		free_page((unsigned long) map[n].ptr);
}