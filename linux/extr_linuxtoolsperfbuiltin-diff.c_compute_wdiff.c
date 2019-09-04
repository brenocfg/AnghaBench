#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_4__ {int computed; int wdiff; } ;
struct TYPE_3__ {int period; } ;
struct hist_entry {TYPE_2__ diff; TYPE_1__ stat; } ;
typedef  int s64 ;

/* Variables and functions */
 int compute_wdiff_w1 ; 
 int compute_wdiff_w2 ; 

__attribute__((used)) static s64 compute_wdiff(struct hist_entry *he, struct hist_entry *pair)
{
	u64 old_period = he->stat.period;
	u64 new_period = pair->stat.period;

	pair->diff.computed = true;
	pair->diff.wdiff = new_period * compute_wdiff_w2 -
			   old_period * compute_wdiff_w1;

	return pair->diff.wdiff;
}