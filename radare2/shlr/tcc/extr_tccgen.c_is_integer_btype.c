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
 int VT_INT16 ; 
 int VT_INT32 ; 
 int VT_INT64 ; 
 int VT_INT8 ; 

__attribute__((used)) static inline int is_integer_btype(int bt) {
	return bt == VT_INT8 || bt == VT_INT16 || bt == VT_INT32 || bt == VT_INT64;
}