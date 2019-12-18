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
struct TYPE_4__ {struct TYPE_4__* propName; int /*<<< orphan*/  vProp; } ;
typedef  TYPE_1__ IDxDiagContainerImpl_Property ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_property_information(IDxDiagContainerImpl_Property *prop)
{
    VariantClear(&prop->vProp);
    HeapFree(GetProcessHeap(), 0, prop->propName);
    HeapFree(GetProcessHeap(), 0, prop);
}