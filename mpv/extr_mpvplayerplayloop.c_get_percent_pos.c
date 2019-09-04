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
struct MPContext {int dummy; } ;

/* Variables and functions */
 double get_current_pos_ratio (struct MPContext*,int) ; 

int get_percent_pos(struct MPContext *mpctx)
{
    double pos = get_current_pos_ratio(mpctx, false);
    return pos < 0 ? -1 : pos * 100;
}