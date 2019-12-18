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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut16 ;

/* Variables and functions */

__attribute__((used)) static ut16 swap2(ut16 sv) {
	ut16 rv;
	ut8 *s = (ut8 *)(void *)&sv;
	ut8 *d = (ut8 *)(void *)&rv;
	d[0] = s[1];
	d[1] = s[0];
	return rv;
}