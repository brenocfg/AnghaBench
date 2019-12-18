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
struct TYPE_7__ {scalar_t__ hash; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* Free ) (TYPE_1__*,scalar_t__) ;} ;
typedef  TYPE_1__ ISzAlloc ;
typedef  TYPE_2__ CMatchFinder ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void MatchFinder_FreeThisClassMemory(CMatchFinder *p, ISzAlloc *alloc)
{
  alloc->Free(alloc, p->hash);
  p->hash = 0;
}