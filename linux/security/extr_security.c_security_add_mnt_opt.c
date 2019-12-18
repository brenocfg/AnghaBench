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
 int /*<<< orphan*/  EINVAL ; 
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,int,void**) ; 
 int /*<<< orphan*/  sb_add_mnt_opt ; 

int security_add_mnt_opt(const char *option, const char *val, int len,
			 void **mnt_opts)
{
	return call_int_hook(sb_add_mnt_opt, -EINVAL,
					option, val, len, mnt_opts);
}