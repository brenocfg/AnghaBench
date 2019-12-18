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
 char* strstr (char*,char*) ; 

__attribute__((used)) static char* is_type(char *type) {
	char *name = NULL;
	if ((name = strstr (type, "=type")) ||
		(name = strstr (type, "=struct")) ||
		(name = strstr (type, "=union")) ||
		(name = strstr (type, "=enum")) ||
		(name = strstr (type, "=typedef")) ||
		(name = strstr (type, "=func"))) {
		return name;
	}
	return NULL;
}