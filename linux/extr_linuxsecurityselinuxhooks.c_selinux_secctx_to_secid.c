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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int security_context_to_sid (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selinux_state ; 

__attribute__((used)) static int selinux_secctx_to_secid(const char *secdata, u32 seclen, u32 *secid)
{
	return security_context_to_sid(&selinux_state, secdata, seclen,
				       secid, GFP_KERNEL);
}