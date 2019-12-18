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
struct IOProcList {scalar_t__ fourCC; struct IOProcList* pNext; } ;
typedef  scalar_t__ FOURCC ;

/* Variables and functions */
 struct IOProcList* pIOProcListAnchor ; 

__attribute__((used)) static struct IOProcList*	MMIO_FindProcNode(FOURCC fccIOProc)
{
    struct IOProcList*	pListNode;

    for (pListNode = pIOProcListAnchor; pListNode; pListNode = pListNode->pNext) {
	if (pListNode->fourCC == fccIOProc) {
	    return pListNode;
	}
    }
    return NULL;
}