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
typedef  size_t UInt32 ;
struct TYPE_4__ {scalar_t__ (* Alloc ) (TYPE_1__*,size_t) ;} ;
typedef  TYPE_1__ ISzAlloc ;
typedef  int /*<<< orphan*/  CLzRef ;

/* Variables and functions */
 scalar_t__ stub1 (TYPE_1__*,size_t) ; 

__attribute__((used)) static CLzRef* AllocRefs(UInt32 num, ISzAlloc *alloc)
{
  size_t sizeInBytes = (size_t)num * sizeof(CLzRef);
  if (sizeInBytes / sizeof(CLzRef) != num)
    return 0;
  return (CLzRef *)alloc->Alloc(alloc, sizeInBytes);
}