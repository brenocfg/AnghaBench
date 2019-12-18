#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* overrides; TYPE_1__* partstate; } ;
struct TYPE_6__ {int iPartId; int iStateId; struct TYPE_6__* next; } ;
typedef  TYPE_1__* PTHEME_PARTSTATE ;
typedef  TYPE_2__* PTHEME_CLASS ;

/* Variables and functions */

PTHEME_PARTSTATE MSSTYLES_FindPartState(PTHEME_CLASS tc, int iPartId, int iStateId, PTHEME_CLASS *tcNext)
{
    PTHEME_PARTSTATE cur = tc->partstate;
    while(cur) {
        if(cur->iPartId == iPartId && cur->iStateId == iStateId) {
            if(tcNext) *tcNext = tc->overrides;
            return cur;
        }
        cur = cur->next;
    }
    if(tc->overrides) return MSSTYLES_FindPartState(tc->overrides, iPartId, iStateId, tcNext);
    return NULL;
}