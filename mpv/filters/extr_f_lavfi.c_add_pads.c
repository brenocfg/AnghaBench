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
struct lavfi {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  pad_idx; int /*<<< orphan*/  filter_ctx; struct TYPE_3__* next; } ;
typedef  TYPE_1__ AVFilterInOut ;

/* Variables and functions */
 int /*<<< orphan*/  add_pad (struct lavfi*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void add_pads(struct lavfi *c, int dir, AVFilterInOut *l, bool first_init)
{
    int index = 0;
    for (; l; l = l->next)
        add_pad(c, dir, index++, l->filter_ctx, l->pad_idx, l->name, first_init);
}