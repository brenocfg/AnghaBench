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
 int /*<<< orphan*/  r_name_filter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_str_trim (char*) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static char *filter_item_name(const char *name) {
	char *res = strdup (name);
	if (!res) {
		return NULL;
	}

	r_str_trim (res);
	r_name_filter (res, 0);
	return res;
}