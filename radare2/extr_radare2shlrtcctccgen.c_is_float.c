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
 int VT_BTYPE ; 
 int VT_DOUBLE ; 
 int VT_FLOAT ; 
 int VT_LDOUBLE ; 
 int VT_QFLOAT ; 

int is_float(int t) {
	int bt;
	bt = t & VT_BTYPE;
	return bt == VT_LDOUBLE || bt == VT_DOUBLE || bt == VT_FLOAT || bt == VT_QFLOAT;
}