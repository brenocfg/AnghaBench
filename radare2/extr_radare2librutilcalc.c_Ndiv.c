#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int d; int n; } ;
typedef  TYPE_1__ RNumCalcValue ;

/* Variables and functions */

__attribute__((used)) static inline RNumCalcValue Ndiv(RNumCalcValue n, RNumCalcValue v) {
	if (v.d) {
		n.d /= v.d;
	} else {
		n.d = 0;
	}
	if (v.n) {
		n.n /= v.n;
	} else {
		n.n = 0;
	}
	return n;
}