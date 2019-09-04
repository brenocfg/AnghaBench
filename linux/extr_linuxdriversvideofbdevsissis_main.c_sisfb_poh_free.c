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
typedef  scalar_t__ u32 ;
struct SIS_OH {scalar_t__ offset; scalar_t__ size; struct SIS_OH* poh_next; } ;
struct SIS_HEAP {struct SIS_OH oh_free; int /*<<< orphan*/  max_freesize; struct SIS_OH oh_used; } ;

/* Variables and functions */
 int /*<<< orphan*/  sisfb_delete_node (struct SIS_OH*) ; 
 int /*<<< orphan*/  sisfb_free_node (struct SIS_HEAP*,struct SIS_OH*) ; 
 int /*<<< orphan*/  sisfb_insert_node (struct SIS_OH*,struct SIS_OH*) ; 

__attribute__((used)) static struct SIS_OH *
sisfb_poh_free(struct SIS_HEAP *memheap, u32 base)
{
	struct SIS_OH *pohThis;
	struct SIS_OH *poh_freed;
	struct SIS_OH *poh_prev;
	struct SIS_OH *poh_next;
	u32    ulUpper;
	u32    ulLower;
	int    foundNode = 0;

	poh_freed = memheap->oh_used.poh_next;

	while(poh_freed != &memheap->oh_used) {
		if(poh_freed->offset == base) {
			foundNode = 1;
			break;
		}

		poh_freed = poh_freed->poh_next;
	}

	if(!foundNode)
		return NULL;

	memheap->max_freesize += poh_freed->size;

	poh_prev = poh_next = NULL;
	ulUpper = poh_freed->offset + poh_freed->size;
	ulLower = poh_freed->offset;

	pohThis = memheap->oh_free.poh_next;

	while(pohThis != &memheap->oh_free) {
		if(pohThis->offset == ulUpper) {
			poh_next = pohThis;
		} else if((pohThis->offset + pohThis->size) == ulLower) {
			poh_prev = pohThis;
		}
		pohThis = pohThis->poh_next;
	}

	sisfb_delete_node(poh_freed);

	if(poh_prev && poh_next) {
		poh_prev->size += (poh_freed->size + poh_next->size);
		sisfb_delete_node(poh_next);
		sisfb_free_node(memheap, poh_freed);
		sisfb_free_node(memheap, poh_next);
		return poh_prev;
	}

	if(poh_prev) {
		poh_prev->size += poh_freed->size;
		sisfb_free_node(memheap, poh_freed);
		return poh_prev;
	}

	if(poh_next) {
		poh_next->size += poh_freed->size;
		poh_next->offset = poh_freed->offset;
		sisfb_free_node(memheap, poh_freed);
		return poh_next;
	}

	sisfb_insert_node(&memheap->oh_free, poh_freed);

	return poh_freed;
}