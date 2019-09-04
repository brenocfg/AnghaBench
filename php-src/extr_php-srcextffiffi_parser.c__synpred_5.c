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
 int YY__LPAREN ; 
 int check_type_name_start (int) ; 
 int get_sym () ; 

__attribute__((used)) static int _synpred_5(int sym) {
	if (sym != YY__LPAREN) {
		return -1;
	}
	sym = get_sym();
	sym = check_type_name_start(sym);
	if (sym == -1) {
		return -1;
	}
	return sym;
}