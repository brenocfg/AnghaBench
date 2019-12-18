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
 int ceil (double) ; 
 int max_hlist_size ; 

void set_hlist_size(double throughput_wait_secs) {
   int new_size;
   new_size = ceil(10.0 / throughput_wait_secs);
   max_hlist_size = (new_size > 1) ? new_size : max_hlist_size;
}