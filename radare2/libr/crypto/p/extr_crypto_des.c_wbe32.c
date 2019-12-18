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

/* Variables and functions */

__attribute__((used)) static void wbe32(ut8 *buf4, ut32 val) {
	buf4[0] = (val >> 24);
	buf4[1] = (val >> 16) & 0xFF;
	buf4[2] = (val >> 8) & 0xFF;
	buf4[3] = val & 0xFF;
}