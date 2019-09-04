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
 char* strchr (char const*,char) ; 

__attribute__((used)) static int gb_reg_idx (char r) {
	const char *rstr = "bcdehla";
	const char *ptr = strchr (rstr, r);
	return ptr?(int)(size_t)(ptr-rstr):-1;
}