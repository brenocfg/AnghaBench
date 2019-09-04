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
 char* strchr (char const*,char) ; 

__attribute__((used)) static ut8 get_register_id(char reg) {
	const char *regs = "ABCXYZIJ";
	const char *p = strchr (regs, reg);
	return p? (int)(size_t)(p-regs): 0;
}