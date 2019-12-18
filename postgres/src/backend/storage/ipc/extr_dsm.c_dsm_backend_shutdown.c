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
 int dlist_head_element (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlist_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsm_detach (int) ; 
 int dsm_segment ; 
 int /*<<< orphan*/  dsm_segment_list ; 
 int /*<<< orphan*/  node ; 
 int seg ; 

void
dsm_backend_shutdown(void)
{
	while (!dlist_is_empty(&dsm_segment_list))
	{
		dsm_segment *seg;

		seg = dlist_head_element(dsm_segment, node, &dsm_segment_list);
		dsm_detach(seg);
	}
}