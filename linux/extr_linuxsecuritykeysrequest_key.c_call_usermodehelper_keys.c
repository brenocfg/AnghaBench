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
struct subprocess_info {int dummy; } ;
struct key {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int call_usermodehelper_exec (struct subprocess_info*,int) ; 
 struct subprocess_info* call_usermodehelper_setup (char const*,char**,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct key*) ; 
 int /*<<< orphan*/  key_get (struct key*) ; 
 int /*<<< orphan*/  umh_keys_cleanup ; 
 int /*<<< orphan*/  umh_keys_init ; 

__attribute__((used)) static int call_usermodehelper_keys(const char *path, char **argv, char **envp,
					struct key *session_keyring, int wait)
{
	struct subprocess_info *info;

	info = call_usermodehelper_setup(path, argv, envp, GFP_KERNEL,
					  umh_keys_init, umh_keys_cleanup,
					  session_keyring);
	if (!info)
		return -ENOMEM;

	key_get(session_keyring);
	return call_usermodehelper_exec(info, wait);
}