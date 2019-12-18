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
typedef  scalar_t__ OSStatus ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,char const*,int) ; 
 scalar_t__ noErr ; 

__attribute__((used)) static inline bool enum_success(OSStatus stat, const char *msg)
{
	if (stat != noErr) {
		blog(LOG_WARNING, "[coreaudio_enum_devices] %s failed: %d", msg,
		     (int)stat);
		return false;
	}

	return true;
}