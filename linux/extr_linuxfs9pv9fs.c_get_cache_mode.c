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
 int CACHE_FSCACHE ; 
 int CACHE_LOOSE ; 
 int CACHE_MMAP ; 
 int CACHE_NONE ; 
 int EINVAL ; 
 int /*<<< orphan*/  P9_DEBUG_9P ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pr_info (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int get_cache_mode(char *s)
{
	int version = -EINVAL;

	if (!strcmp(s, "loose")) {
		version = CACHE_LOOSE;
		p9_debug(P9_DEBUG_9P, "Cache mode: loose\n");
	} else if (!strcmp(s, "fscache")) {
		version = CACHE_FSCACHE;
		p9_debug(P9_DEBUG_9P, "Cache mode: fscache\n");
	} else if (!strcmp(s, "mmap")) {
		version = CACHE_MMAP;
		p9_debug(P9_DEBUG_9P, "Cache mode: mmap\n");
	} else if (!strcmp(s, "none")) {
		version = CACHE_NONE;
		p9_debug(P9_DEBUG_9P, "Cache mode: none\n");
	} else
		pr_info("Unknown Cache mode %s\n", s);
	return version;
}