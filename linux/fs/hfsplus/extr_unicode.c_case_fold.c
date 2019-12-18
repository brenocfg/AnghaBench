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
typedef  int u16 ;

/* Variables and functions */
 int* hfsplus_case_fold_table ; 

__attribute__((used)) static inline u16 case_fold(u16 c)
{
	u16 tmp;

	tmp = hfsplus_case_fold_table[c >> 8];
	if (tmp)
		tmp = hfsplus_case_fold_table[tmp + (c & 0xff)];
	else
		tmp = c;
	return tmp;
}