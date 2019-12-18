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
 int /*<<< orphan*/  WARN_ONCE (int,char*,char*,char*,char*,char*,char*,char*,unsigned long,unsigned long) ; 

void usercopy_warn(const char *name, const char *detail, bool to_user,
		   unsigned long offset, unsigned long len)
{
	WARN_ONCE(1, "Bad or missing usercopy whitelist? Kernel memory %s attempt detected %s %s%s%s%s (offset %lu, size %lu)!\n",
		 to_user ? "exposure" : "overwrite",
		 to_user ? "from" : "to",
		 name ? : "unknown?!",
		 detail ? " '" : "", detail ? : "", detail ? "'" : "",
		 offset, len);
}