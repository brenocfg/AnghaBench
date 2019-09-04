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
struct SIS_OH {struct SIS_OH* poh_next; } ;
struct SIS_HEAP {struct SIS_OH* poh_freelist; } ;

/* Variables and functions */

__attribute__((used)) static void
sisfb_free_node(struct SIS_HEAP *memheap, struct SIS_OH *poh)
{
	if(poh == NULL)
		return;

	poh->poh_next = memheap->poh_freelist;
	memheap->poh_freelist = poh;
}