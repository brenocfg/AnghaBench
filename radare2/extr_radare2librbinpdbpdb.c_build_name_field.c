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
 int /*<<< orphan*/  r_name_filter (char*,int) ; 
 int /*<<< orphan*/  r_str_replace_char (char*,char,char) ; 
 char* strdup (char*) ; 

void build_name_field(char *name, char **name_field) {
	if (name_field) {
		*name_field = name? strdup (name): NULL;
		r_name_filter (*name_field, -1);
		r_str_replace_char (*name_field, ':', '_');
	}
}