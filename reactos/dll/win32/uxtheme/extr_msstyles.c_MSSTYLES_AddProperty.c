#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* properties; scalar_t__ iPartId; scalar_t__ iStateId; } ;
struct TYPE_8__ {int iPrimitiveType; int iPropertyId; struct TYPE_8__* next; int /*<<< orphan*/  origin; int /*<<< orphan*/  dwValueLen; int /*<<< orphan*/  lpValue; } ;
typedef  int /*<<< orphan*/  THEME_PROPERTY ;
typedef  TYPE_1__* PTHEME_PROPERTY ;
typedef  TYPE_2__* PTHEME_PARTSTATE ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* MSSTYLES_PSFindProperty (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  PO_CLASS ; 
 int /*<<< orphan*/  PO_GLOBAL ; 
 int /*<<< orphan*/  PO_PART ; 
 int /*<<< orphan*/  PO_STATE ; 

__attribute__((used)) static PTHEME_PROPERTY MSSTYLES_AddProperty(PTHEME_PARTSTATE ps, int iPropertyPrimitive, int iPropertyId, LPCWSTR lpValue, DWORD dwValueLen, BOOL isGlobal)
{
    PTHEME_PROPERTY cur = MSSTYLES_PSFindProperty(ps, iPropertyPrimitive, iPropertyId);
    /* Should duplicate properties overwrite the original, or be ignored? */
    if(cur) return cur;

    cur = HeapAlloc(GetProcessHeap(), 0, sizeof(THEME_PROPERTY));
    cur->iPrimitiveType = iPropertyPrimitive;
    cur->iPropertyId = iPropertyId;
    cur->lpValue = lpValue;
    cur->dwValueLen = dwValueLen;

    if(ps->iStateId)
        cur->origin = PO_STATE;
    else if(ps->iPartId)
        cur->origin = PO_PART;
    else if(isGlobal)
        cur->origin = PO_GLOBAL;
    else
        cur->origin = PO_CLASS;

    cur->next = ps->properties;
    ps->properties = cur;
    return cur;
}