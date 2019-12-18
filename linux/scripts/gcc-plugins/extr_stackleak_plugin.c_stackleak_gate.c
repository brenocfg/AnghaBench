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
typedef  scalar_t__ tree ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_ATTRIBUTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_STRING_POINTER (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  current_function_decl ; 
 scalar_t__ lookup_attribute (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ track_frame_size ; 

__attribute__((used)) static bool stackleak_gate(void)
{
	tree section;

	section = lookup_attribute("section",
				   DECL_ATTRIBUTES(current_function_decl));
	if (section && TREE_VALUE(section)) {
		section = TREE_VALUE(TREE_VALUE(section));

		if (!strncmp(TREE_STRING_POINTER(section), ".init.text", 10))
			return false;
		if (!strncmp(TREE_STRING_POINTER(section), ".devinit.text", 13))
			return false;
		if (!strncmp(TREE_STRING_POINTER(section), ".cpuinit.text", 13))
			return false;
		if (!strncmp(TREE_STRING_POINTER(section), ".meminit.text", 13))
			return false;
	}

	return track_frame_size >= 0;
}