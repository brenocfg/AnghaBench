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
 int /*<<< orphan*/  r_return_val_if_fail (int /*<<< orphan*/ ,int) ; 
 scalar_t__ r_str_startswith (char const*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 char* strstr (char const*,char*) ; 

__attribute__((used)) static bool r_io_def_mmap_check_default (const char *filename) {
	r_return_val_if_fail (filename && *filename, false);
	if (r_str_startswith (filename, "file://")) {
		filename += strlen ("file://");
	}
	const char * peekaboo = (!strncmp (filename, "nocache://", 10))
		? NULL : strstr (filename, "://");
	return (!peekaboo || (peekaboo - filename) > 10);
}