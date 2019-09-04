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

/* Variables and functions */
 int* i4004_ins_len ; 

__attribute__((used)) static int i4004_get_ins_len (ut8 hex) {
	ut8 high = (hex & 0xf0)>>4;
	int ret = i4004_ins_len[high];
	if (ret == 3) {
		ret = (hex & 1) ? 1 : 2;
	}
	return ret;
}