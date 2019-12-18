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
struct coreaudio_data {int /*<<< orphan*/  device_name; } ;
typedef  scalar_t__ OSStatus ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ noErr ; 

__attribute__((used)) static inline bool ca_success(OSStatus stat, struct coreaudio_data *ca,
			      const char *func, const char *action)
{
	if (stat != noErr) {
		blog(LOG_WARNING, "[%s]:[device '%s'] %s failed: %d", func,
		     ca->device_name, action, (int)stat);
		return false;
	}

	return true;
}