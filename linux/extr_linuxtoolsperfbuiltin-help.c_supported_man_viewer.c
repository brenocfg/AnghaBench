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
 int /*<<< orphan*/  strncasecmp (char*,char const*,size_t) ; 

__attribute__((used)) static int supported_man_viewer(const char *name, size_t len)
{
	return (!strncasecmp("man", name, len) ||
		!strncasecmp("woman", name, len) ||
		!strncasecmp("konqueror", name, len));
}