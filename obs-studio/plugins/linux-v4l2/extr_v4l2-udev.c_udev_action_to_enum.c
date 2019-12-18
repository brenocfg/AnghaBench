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
typedef  enum udev_action { ____Placeholder_udev_action } udev_action ;

/* Variables and functions */
 int UDEV_ACTION_ADDED ; 
 int UDEV_ACTION_REMOVED ; 
 int UDEV_ACTION_UNKNOWN ; 
 int /*<<< orphan*/  strncmp (char*,char const*,int) ; 

__attribute__((used)) static enum udev_action udev_action_to_enum(const char *action)
{
	if (!action)
		return UDEV_ACTION_UNKNOWN;

	if (!strncmp("add", action, 3))
		return UDEV_ACTION_ADDED;
	if (!strncmp("remove", action, 6))
		return UDEV_ACTION_REMOVED;

	return UDEV_ACTION_UNKNOWN;
}