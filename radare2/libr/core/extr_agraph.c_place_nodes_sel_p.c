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
 int R_MAX (int,int) ; 
 int R_MIN (int,int) ; 

__attribute__((used)) static int place_nodes_sel_p(int newval, int oldval, int is_first, int is_left) {
	if (is_first) {
		return newval;
	}
	if (is_left) {
		return R_MAX (oldval, newval);
	}
	return R_MIN (oldval, newval);
}