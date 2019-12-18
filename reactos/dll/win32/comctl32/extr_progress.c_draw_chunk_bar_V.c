#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
struct TYPE_8__ {int /*<<< orphan*/  hbrBk; int /*<<< orphan*/  hdc; scalar_t__ ledGap; int /*<<< orphan*/  hbrBar; scalar_t__ ledW; TYPE_1__ rect; } ;
struct TYPE_7__ {int bottom; int top; int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__ ProgressDrawInfo ;

/* Variables and functions */
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 void* max (scalar_t__,int) ; 

__attribute__((used)) static void draw_chunk_bar_V (const ProgressDrawInfo* di, int start, int end)
{
    RECT r;
    int top = di->rect.bottom - end;
    r.left = di->rect.left;
    r.right = di->rect.right;
    r.bottom = di->rect.bottom - start;
    while (r.bottom > top)
    {
        r.top = max (r.bottom - di->ledW, top);
        FillRect (di->hdc, &r, di->hbrBar);
        r.bottom = r.top;
        r.top = max (r.bottom - di->ledGap, top);
        FillRect (di->hdc, &r, di->hbrBk);
        r.bottom = r.top;
    }
}