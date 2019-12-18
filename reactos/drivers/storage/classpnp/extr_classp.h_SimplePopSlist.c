#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* Next; } ;
typedef  TYPE_1__ SLIST_ENTRY ;

/* Variables and functions */

__attribute__((used)) static inline SLIST_ENTRY *SimplePopSlist(SLIST_ENTRY *SListHdr)
{
    SLIST_ENTRY *sListEntry = SListHdr->Next;
    if (sListEntry){
        SListHdr->Next = sListEntry->Next;
        sListEntry->Next = NULL;
    }
    return sListEntry;
}