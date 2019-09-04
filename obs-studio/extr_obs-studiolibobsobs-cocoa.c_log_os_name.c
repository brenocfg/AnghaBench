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
typedef  scalar_t__ id ;
typedef  int /*<<< orphan*/  SEL ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ objc_msgSend (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sel_registerName (char*) ; 

__attribute__((used)) static void log_os_name(id pi, SEL UTF8String)
{
	unsigned long os_id = (unsigned long)objc_msgSend(pi,
			sel_registerName("operatingSystem"));

	id os = objc_msgSend(pi,
			sel_registerName("operatingSystemName"));
	const char *name = (const char*)objc_msgSend(os, UTF8String);

	if (os_id == 5 /*NSMACHOperatingSystem*/) {
		blog(LOG_INFO, "OS Name: Mac OS X (%s)", name);
		return;
	}

	blog(LOG_INFO, "OS Name: %s", name ? name : "Unknown");
}