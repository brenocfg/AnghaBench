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
typedef  int /*<<< orphan*/ * PTHEME_PROPERTY ;
typedef  int /*<<< orphan*/  PTHEME_PARTSTATE ;
typedef  scalar_t__ PTHEME_CLASS ;

/* Variables and functions */
 int /*<<< orphan*/  MSSTYLES_FindPartState (scalar_t__,int,int,scalar_t__*) ; 
 int /*<<< orphan*/ * MSSTYLES_PSFindProperty (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,int,int,int) ; 

PTHEME_PROPERTY MSSTYLES_FindProperty(PTHEME_CLASS tc, int iPartId, int iStateId, int iPropertyPrimitive, int iPropertyId)
{
    PTHEME_CLASS next = tc;
    PTHEME_PARTSTATE ps;
    PTHEME_PROPERTY tp;

    TRACE("(%p, %d, %d, %d)\n", tc, iPartId, iStateId, iPropertyId);
     /* Try and find an exact match on part & state */
    while(next && (ps = MSSTYLES_FindPartState(next, iPartId, iStateId, &next))) {
        if((tp = MSSTYLES_PSFindProperty(ps, iPropertyPrimitive, iPropertyId))) {
            return tp;
        }
    }
    /* If that fails, and we didn't already try it, search for just part */
    if(iStateId != 0)
        iStateId = 0;
    /* As a last ditch attempt..go for just class */
    else if(iPartId != 0)
        iPartId = 0;
    else
        return NULL;

    if((tp = MSSTYLES_FindProperty(tc, iPartId, iStateId, iPropertyPrimitive, iPropertyId)))
        return tp;
    return NULL;
}