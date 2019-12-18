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
 char* strchr (char*,int /*<<< orphan*/ ) ; 

char *phpdbg_get_property_key(char *key) {
	if (*key != 0) {
		return key;
	}
	return strchr(key + 1, 0) + 1;
}