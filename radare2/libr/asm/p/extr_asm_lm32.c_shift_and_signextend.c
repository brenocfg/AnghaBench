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
typedef  int ut8 ;
typedef  int ut32 ;
typedef  int st32 ;

/* Variables and functions */

__attribute__((used)) static st32 shift_and_signextend(ut8 shift, ut8 sign_loc, ut32 val) {
	ut32 tmp = val << shift;
	if (tmp & (1 << (shift + sign_loc))) {
		tmp |= ~((1 << (shift + sign_loc + 1)) - 1);
	}
	return tmp;
}