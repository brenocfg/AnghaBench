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
struct TYPE_6__ {TYPE_2__* lpstrName; } ;
struct TYPE_7__ {scalar_t__ pFontEventsCP; scalar_t__ pPropertyNotifyCP; TYPE_1__ description; } ;
typedef  TYPE_2__ OLEFontImpl ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  IConnectionPoint_Release (scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*) ; 

__attribute__((used)) static void OLEFontImpl_Destroy(OLEFontImpl* fontDesc)
{
  TRACE("(%p)\n", fontDesc);

  HeapFree(GetProcessHeap(), 0, fontDesc->description.lpstrName);

  if (fontDesc->pPropertyNotifyCP)
      IConnectionPoint_Release(fontDesc->pPropertyNotifyCP);
  if (fontDesc->pFontEventsCP)
      IConnectionPoint_Release(fontDesc->pFontEventsCP);

  HeapFree(GetProcessHeap(), 0, fontDesc);
}