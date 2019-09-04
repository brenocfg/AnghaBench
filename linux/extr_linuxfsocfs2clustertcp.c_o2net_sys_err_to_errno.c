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
typedef  enum o2net_system_error { ____Placeholder_o2net_system_error } o2net_system_error ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int O2NET_ERR_MAX ; 
 int O2NET_ERR_NONE ; 
 int* o2net_sys_err_translations ; 

__attribute__((used)) static inline int o2net_sys_err_to_errno(enum o2net_system_error err)
{
	int trans;
	BUG_ON(err >= O2NET_ERR_MAX);
	trans = o2net_sys_err_translations[err];

	/* Just in case we mess up the translation table above */
	BUG_ON(err != O2NET_ERR_NONE && trans == 0);
	return trans;
}