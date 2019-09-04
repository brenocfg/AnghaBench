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
struct tx_policy {int* raw; int /*<<< orphan*/  defined; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tx_policy_dump(struct tx_policy *policy)
{
	pr_debug("[TX policy] %.1X%.1X%.1X%.1X%.1X%.1X%.1X%.1X %.1X%.1X%.1X%.1X%.1X%.1X%.1X%.1X %.1X%.1X%.1X%.1X%.1X%.1X%.1X%.1X: %d\n",
		 policy->raw[0] & 0x0F,  policy->raw[0] >> 4,
		 policy->raw[1] & 0x0F,  policy->raw[1] >> 4,
		 policy->raw[2] & 0x0F,  policy->raw[2] >> 4,
		 policy->raw[3] & 0x0F,  policy->raw[3] >> 4,
		 policy->raw[4] & 0x0F,  policy->raw[4] >> 4,
		 policy->raw[5] & 0x0F,  policy->raw[5] >> 4,
		 policy->raw[6] & 0x0F,  policy->raw[6] >> 4,
		 policy->raw[7] & 0x0F,  policy->raw[7] >> 4,
		 policy->raw[8] & 0x0F,  policy->raw[8] >> 4,
		 policy->raw[9] & 0x0F,  policy->raw[9] >> 4,
		 policy->raw[10] & 0x0F,  policy->raw[10] >> 4,
		 policy->raw[11] & 0x0F,  policy->raw[11] >> 4,
		 policy->defined);
}