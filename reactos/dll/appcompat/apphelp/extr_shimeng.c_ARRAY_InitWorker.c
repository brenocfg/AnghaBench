#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ItemSize__; scalar_t__ MaxSize__; scalar_t__ Size__; int /*<<< orphan*/ * Data__; } ;
typedef  TYPE_1__* PARRAY ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static inline BOOL ARRAY_InitWorker(PARRAY Array, DWORD ItemSize)
{
    Array->Data__ = NULL;
    Array->Size__ = Array->MaxSize__ = 0;
    Array->ItemSize__ = ItemSize;

    return TRUE;
}