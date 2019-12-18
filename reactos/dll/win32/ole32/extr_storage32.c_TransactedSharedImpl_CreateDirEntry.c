#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* scratch; } ;
typedef  TYPE_2__ TransactedSharedImpl ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
typedef  int /*<<< orphan*/  StorageBaseImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DirRef ;
typedef  int /*<<< orphan*/  DirEntry ;

/* Variables and functions */
 int /*<<< orphan*/  StorageBaseImpl_CreateDirEntry (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT TransactedSharedImpl_CreateDirEntry(StorageBaseImpl *base,
  const DirEntry *newData, DirRef *index)
{
  TransactedSharedImpl* This = (TransactedSharedImpl*) base;

  return StorageBaseImpl_CreateDirEntry(&This->scratch->base,
    newData, index);
}