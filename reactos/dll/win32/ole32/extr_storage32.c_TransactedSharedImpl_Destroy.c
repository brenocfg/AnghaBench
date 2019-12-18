#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* scratch; TYPE_1__* transactedParent; int /*<<< orphan*/  base; } ;
typedef  TYPE_4__ TransactedSharedImpl ;
struct TYPE_7__ {int /*<<< orphan*/  IStorage_iface; } ;
struct TYPE_8__ {TYPE_2__ base; } ;
struct TYPE_6__ {int /*<<< orphan*/  IStorage_iface; } ;
typedef  int /*<<< orphan*/  StorageBaseImpl ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  IStorage_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TransactedSharedImpl_Invalidate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void TransactedSharedImpl_Destroy( StorageBaseImpl *iface)
{
  TransactedSharedImpl* This = (TransactedSharedImpl*) iface;

  TransactedSharedImpl_Invalidate(&This->base);
  IStorage_Release(&This->transactedParent->IStorage_iface);
  IStorage_Release(&This->scratch->base.IStorage_iface);
  HeapFree(GetProcessHeap(), 0, This);
}