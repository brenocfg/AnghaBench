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
typedef  int ut32 ;

/* Variables and functions */
 char* strdup (char const*) ; 

char *get_cmp_op(ut32 idx) {
	const char *res = NULL;
	switch (idx) {
	case 0: res = "=="; break;
	case 1: res = "!="; break;
	case 2: res = "<"; break;
	case 3: res = ">="; break;
	}
	return res? strdup (res): NULL;
}