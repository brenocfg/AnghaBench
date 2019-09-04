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
 scalar_t__ r_file_is_directory (char*) ; 
 int rafind_open_dir (char*) ; 
 int rafind_open_file (char*) ; 

__attribute__((used)) static int rafind_open(char *file) {
	if (r_file_is_directory (file)) {
		return rafind_open_dir (file);
	}

	return rafind_open_file (file);
}