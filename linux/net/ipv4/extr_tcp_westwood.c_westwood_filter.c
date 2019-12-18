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
typedef  int u32 ;
struct westwood {int bw_ns_est; int bw_est; int bk; } ;

/* Variables and functions */
 void* westwood_do_filter (int,int) ; 

__attribute__((used)) static void westwood_filter(struct westwood *w, u32 delta)
{
	/* If the filter is empty fill it with the first sample of bandwidth  */
	if (w->bw_ns_est == 0 && w->bw_est == 0) {
		w->bw_ns_est = w->bk / delta;
		w->bw_est = w->bw_ns_est;
	} else {
		w->bw_ns_est = westwood_do_filter(w->bw_ns_est, w->bk / delta);
		w->bw_est = westwood_do_filter(w->bw_est, w->bw_ns_est);
	}
}