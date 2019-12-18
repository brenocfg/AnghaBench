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
struct TYPE_6__ {TYPE_1__* baseVtbl; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* WriteDirEntry ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ;} ;
typedef  TYPE_2__ StorageBaseImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DirRef ;
typedef  int /*<<< orphan*/  DirEntry ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline HRESULT StorageBaseImpl_WriteDirEntry(StorageBaseImpl *This,
  DirRef index, const DirEntry *data)
{
  return This->baseVtbl->WriteDirEntry(This, index, data);
}