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
typedef  int /*<<< orphan*/  ULONG_PTR ;
struct TYPE_3__ {int lbStyle; int /*<<< orphan*/  lbHatch; } ;
typedef  TYPE_1__ LOGBRUSH ;
typedef  int /*<<< orphan*/  HGDIOBJ ;
typedef  int /*<<< orphan*/  GpStatus ;

/* Variables and functions */
#define  BS_PATTERN 128 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Ok ; 

__attribute__((used)) static GpStatus free_gdi_logbrush(LOGBRUSH *lb)
{
    switch (lb->lbStyle)
    {
        case BS_PATTERN:
            DeleteObject((HGDIOBJ)(ULONG_PTR)lb->lbHatch);
            break;
    }
    return Ok;
}