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

/* Variables and functions */
 int mp_imgfmt_select_best (int,int,int) ; 

int mp_imgfmt_select_best_list(int *dst, int num_dst, int src)
{
    int best = 0;
    for (int n = 0; n < num_dst; n++)
        best = best ? mp_imgfmt_select_best(best, dst[n], src) : dst[n];
    return best;
}