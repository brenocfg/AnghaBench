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
struct kernel_param {int /*<<< orphan*/ * arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_MAX_RESVPORT ; 
 int /*<<< orphan*/  RPC_MIN_RESVPORT ; 
 int param_set_uint_minmax (char const*,struct kernel_param const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprt_max_resvport ; 
 int /*<<< orphan*/  xprt_min_resvport ; 

__attribute__((used)) static int param_set_portnr(const char *val, const struct kernel_param *kp)
{
	if (kp->arg == &xprt_min_resvport)
		return param_set_uint_minmax(val, kp,
			RPC_MIN_RESVPORT,
			xprt_max_resvport);
	return param_set_uint_minmax(val, kp,
			xprt_min_resvport,
			RPC_MAX_RESVPORT);
}