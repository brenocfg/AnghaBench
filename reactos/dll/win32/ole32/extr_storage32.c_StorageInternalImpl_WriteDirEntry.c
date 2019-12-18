#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  parentStorage; } ;
typedef  TYPE_1__ StorageInternalImpl ;
typedef  int /*<<< orphan*/  StorageBaseImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DirRef ;
typedef  int /*<<< orphan*/  DirEntry ;

/* Variables and functions */
 int /*<<< orphan*/  StorageBaseImpl_WriteDirEntry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static HRESULT StorageInternalImpl_WriteDirEntry(StorageBaseImpl *base,
  DirRef index, const DirEntry *data)
{
  StorageInternalImpl* This = (StorageInternalImpl*) base;

  return StorageBaseImpl_WriteDirEntry(This->parentStorage,
    index, data);
}