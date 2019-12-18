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
 scalar_t__ r_str_startswith (char const*,char*) ; 

__attribute__((used)) static bool isKnownPackage(const char *cn) {
	if (*cn == 'L') {
		if (r_str_startswith (cn, "Lkotlin")) {
			return true;
		}
		if (r_str_startswith (cn, "Lcom/google")) {
			return true;
		}
		if (r_str_startswith (cn, "Lcom/facebook")) {
			return true;
		}
		if (r_str_startswith (cn, "Lokhttp")) {
			return true;
		}
		if (r_str_startswith (cn, "Landroid")) {
			return true;
		}
		if (r_str_startswith (cn, "Lokio")) {
			return true;
		}
	}
	return false;
}