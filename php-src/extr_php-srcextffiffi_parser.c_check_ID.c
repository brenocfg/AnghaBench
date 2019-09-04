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
 int YY_ID ; 
 int get_sym () ; 

__attribute__((used)) static int check_ID(int sym) {
	if (sym != YY_ID) {
		return -1;
	}
	sym = get_sym();
	return sym;
}