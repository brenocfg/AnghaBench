#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct histogram {int dummy; } ;
struct box {int r_min; int r_max; int g_min; int g_max; int b_min; int b_max; int /*<<< orphan*/  score; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  box_count (struct histogram*,struct box*) ; 
 int /*<<< orphan*/  box_score (struct box*) ; 
 scalar_t__ histogram_count (struct histogram*,int,int,int,int,int,int) ; 

__attribute__((used)) static void shrink_box(struct histogram *h, struct box *b)
{
    int i;
    for (i = b->r_min; i <= b->r_max; i++)
        if (histogram_count(h, i, i, b->g_min, b->g_max, b->b_min, b->b_max)) { b->r_min = i; break; }
    for (i = b->r_max; i >= b->r_min; i--)
        if (histogram_count(h, i, i, b->g_min, b->g_max, b->b_min, b->b_max)) { b->r_max = i; break; }
    for (i = b->g_min; i <= b->g_max; i++)
        if (histogram_count(h, b->r_min, b->r_max, i, i, b->b_min, b->b_max)) { b->g_min = i; break; }
    for (i = b->g_max; i >= b->g_min; i--)
        if (histogram_count(h, b->r_min, b->r_max, i, i, b->b_min, b->b_max)) { b->g_max = i; break; }
    for (i = b->b_min; i <= b->b_max; i++)
        if (histogram_count(h, b->r_min, b->r_max, b->g_min, b->g_max, i, i)) { b->b_min = i; break; }
    for (i = b->b_max; i >= b->b_min; i--)
        if (histogram_count(h, b->r_min, b->r_max, b->g_min, b->g_max, i, i)) { b->b_max = i; break; }
    b->count = box_count(h, b);
    b->score = box_score(b);
}