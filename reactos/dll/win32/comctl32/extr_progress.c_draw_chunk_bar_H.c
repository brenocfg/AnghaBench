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
struct TYPE_6__ {int left; int /*<<< orphan*/  bottom; int /*<<< orphan*/  top; } ;
struct TYPE_8__ {int /*<<< orphan*/  hbrBk; int /*<<< orphan*/  hdc; scalar_t__ ledGap; int /*<<< orphan*/  hbrBar; scalar_t__ ledW; TYPE_1__ rect; } ;
struct TYPE_7__ {int left; int right; int /*<<< orphan*/  bottom; int /*<<< orphan*/  top; } ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__ ProgressDrawInfo ;

/* Variables and functions */
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 void* min (scalar_t__,int) ; 

__attribute__((used)) static void draw_chunk_bar_H (const ProgressDrawInfo* di, int start, int end)
{
    RECT r;
    int right = di->rect.left + end;
    r.left = di->rect.left + start;
    r.top = di->rect.top;
    r.bottom = di->rect.bottom;
    while (r.left < right)
    {
        r.right = min (r.left + di->ledW, right);
        FillRect (di->hdc, &r, di->hbrBar);
        r.left = r.right;
        r.right = min (r.left + di->ledGap, right);
        FillRect (di->hdc, &r, di->hbrBk);
        r.left = r.right;
    }
}