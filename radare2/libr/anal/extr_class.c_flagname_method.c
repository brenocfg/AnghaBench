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
 char* flagname_attr (char*,char const*,char const*) ; 

__attribute__((used)) static char *flagname_method(const char *class_name, const char *meth_name) {
	return flagname_attr ("method", class_name, meth_name);
}