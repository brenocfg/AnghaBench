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
struct r_bin_te_obj_t {int dummy; } ;

/* Variables and functions */

int r_bin_te_get_bits(struct r_bin_te_obj_t* bin) {
	return 32; // It is always 32 bit by now
}