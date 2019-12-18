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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  secctx_to_secid ; 

int security_secctx_to_secid(const char *secdata, u32 seclen, u32 *secid)
{
	*secid = 0;
	return call_int_hook(secctx_to_secid, 0, secdata, seclen, secid);
}