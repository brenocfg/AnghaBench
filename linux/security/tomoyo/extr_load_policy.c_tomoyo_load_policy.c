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
 scalar_t__ CONFIG_SECURITY_TOMOYO_ACTIVATION_TRIGGER ; 
 int /*<<< orphan*/  UMH_WAIT_PROC ; 
 int /*<<< orphan*/  call_usermodehelper (char*,char**,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__) ; 
 scalar_t__ strcmp (char const*,scalar_t__) ; 
 int /*<<< orphan*/  tomoyo_check_profile () ; 
 scalar_t__ tomoyo_loader ; 
 scalar_t__ tomoyo_policy_loaded ; 
 int /*<<< orphan*/  tomoyo_policy_loader_exists () ; 
 scalar_t__ tomoyo_trigger ; 

void tomoyo_load_policy(const char *filename)
{
	static bool done;
	char *argv[2];
	char *envp[3];

	if (tomoyo_policy_loaded || done)
		return;
	if (!tomoyo_trigger)
		tomoyo_trigger = CONFIG_SECURITY_TOMOYO_ACTIVATION_TRIGGER;
	if (strcmp(filename, tomoyo_trigger))
		return;
	if (!tomoyo_policy_loader_exists())
		return;
	done = true;
	pr_info("Calling %s to load policy. Please wait.\n", tomoyo_loader);
	argv[0] = (char *) tomoyo_loader;
	argv[1] = NULL;
	envp[0] = "HOME=/";
	envp[1] = "PATH=/sbin:/bin:/usr/sbin:/usr/bin";
	envp[2] = NULL;
	call_usermodehelper(argv[0], argv, envp, UMH_WAIT_PROC);
	tomoyo_check_profile();
}