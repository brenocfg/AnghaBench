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
struct box {int r_max; int r_min; int g_max; int g_min; int b_max; int b_min; } ;

/* Variables and functions */
 int B_SCALE ; 
 int B_SHIFT ; 
 int G_SCALE ; 
 int G_SHIFT ; 
 int R_SCALE ; 
 int R_SHIFT ; 
 int /*<<< orphan*/  set_avg (int*,int*) ; 
 int /*<<< orphan*/  shrink_box (struct histogram*,struct box*) ; 

__attribute__((used)) static void split_box(struct histogram *h, struct box *b1, struct box *b2)
{
    int r = ((b1->r_max - b1->r_min) << R_SHIFT) * R_SCALE;
    int g = ((b1->g_max - b1->g_min) << G_SHIFT) * G_SCALE;
    int b = ((b1->b_max - b1->b_min) << B_SHIFT) * B_SCALE;

    *b2 = *b1;

    if (r > g)
    {
        if (b > r) set_avg(&b1->b_min, &b2->b_max);
        else set_avg(&b1->r_min, &b2->r_max);
    }
    else
    {
        if (b > g) set_avg(&b1->b_min, &b2->b_max);
        else set_avg(&b1->g_min, &b2->g_max);
    }

    shrink_box(h, b1);
    shrink_box(h, b2);
}