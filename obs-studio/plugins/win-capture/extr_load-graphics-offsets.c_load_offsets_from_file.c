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
struct graphics_offsets {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (char*) ; 
 int load_offsets_from_string (struct graphics_offsets*,char*) ; 
 char* os_quick_read_utf8_file (char const*) ; 

__attribute__((used)) static inline bool load_offsets_from_file(struct graphics_offsets *offsets,
					  const char *file)
{
	char *str = os_quick_read_utf8_file(file);
	bool success = false;
	if (str && *str)
		success = load_offsets_from_string(offsets, str);
	bfree(str);
	return success;
}