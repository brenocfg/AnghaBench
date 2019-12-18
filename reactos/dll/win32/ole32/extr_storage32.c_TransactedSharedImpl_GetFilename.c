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
struct TYPE_2__ {int /*<<< orphan*/  transactedParent; } ;
typedef  TYPE_1__ TransactedSharedImpl ;
typedef  int /*<<< orphan*/  StorageBaseImpl ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  StorageBaseImpl_GetFilename (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT TransactedSharedImpl_GetFilename(StorageBaseImpl* iface, LPWSTR *result)
{
  TransactedSharedImpl* This = (TransactedSharedImpl*) iface;

  return StorageBaseImpl_GetFilename(This->transactedParent, result);
}