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
 int /*<<< orphan*/  DEVKMSG_LOG_MASK_DEFAULT ; 
 int /*<<< orphan*/  DEVKMSG_LOG_MASK_OFF ; 
 int /*<<< orphan*/  DEVKMSG_LOG_MASK_ON ; 
 int EINVAL ; 
 int /*<<< orphan*/  devkmsg_log ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static int __control_devkmsg(char *str)
{
	if (!str)
		return -EINVAL;

	if (!strncmp(str, "on", 2)) {
		devkmsg_log = DEVKMSG_LOG_MASK_ON;
		return 2;
	} else if (!strncmp(str, "off", 3)) {
		devkmsg_log = DEVKMSG_LOG_MASK_OFF;
		return 3;
	} else if (!strncmp(str, "ratelimit", 9)) {
		devkmsg_log = DEVKMSG_LOG_MASK_DEFAULT;
		return 9;
	}
	return -EINVAL;
}