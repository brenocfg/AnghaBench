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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 int /*<<< orphan*/  XT_HASHLIMIT_SCALE_v2 ; 
 scalar_t__ div64_u64 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*,scalar_t__) ; 

__attribute__((used)) static u64 user2rate(u64 user)
{
	if (user != 0) {
		return div64_u64(XT_HASHLIMIT_SCALE_v2, user);
	} else {
		pr_info_ratelimited("invalid rate from userspace: %llu\n",
				    user);
		return 0;
	}
}