#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* parentStorage; } ;
struct TYPE_5__ {int /*<<< orphan*/  IStorage_iface; } ;
typedef  TYPE_2__ IEnumSTATSTGImpl ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  IStorage_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void IEnumSTATSTGImpl_Destroy(IEnumSTATSTGImpl* This)
{
  IStorage_Release(&This->parentStorage->IStorage_iface);
  HeapFree(GetProcessHeap(), 0, This);
}