#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_4__ {int (* exists_var ) (TYPE_1__*,scalar_t__,char*) ;} ;
typedef  TYPE_1__ RPrint ;

/* Variables and functions */
 scalar_t__ IS_ALPHA (char) ; 
 scalar_t__ IS_DIGIT (char) ; 
 int stub1 (TYPE_1__*,scalar_t__,char*) ; 

__attribute__((used)) static bool check_arg_name (RPrint *print, char *p, ut64 func_addr) {
	if (func_addr && print->exists_var) {
		int z;
		for (z = 0; p[z] && (IS_ALPHA (p[z]) || IS_DIGIT (p[z]) || p[z] == '_'); z++) {
			;
		}
		char tmp = p[z];
		p[z] = '\0';
		bool ret = print->exists_var (print, func_addr, p);
		p[z] = tmp;
		return ret;
	}
	return false;
}