#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* lpLink; int /*<<< orphan*/  lpLcl; } ;
typedef  TYPE_1__* LPDDRAWI_DIRECTDRAW_INT ;
typedef  int /*<<< orphan*/  DDRAWI_DIRECTDRAW_INT ;

/* Variables and functions */
 int /*<<< orphan*/  DxHeapMemAlloc (TYPE_1__*,int) ; 

LPDDRAWI_DIRECTDRAW_INT
internal_directdraw_int_alloc(LPDDRAWI_DIRECTDRAW_INT This)
{
    LPDDRAWI_DIRECTDRAW_INT  newThis;
    DxHeapMemAlloc(newThis, sizeof(DDRAWI_DIRECTDRAW_INT));
    if (newThis)
    {
        newThis->lpLcl = This->lpLcl;
        newThis->lpLink = This;
    }

    return  newThis;
}