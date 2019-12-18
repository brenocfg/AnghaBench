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
struct xt_mtchk_param {int /*<<< orphan*/  matchinfo; } ;

/* Variables and functions */
 int recent_mt_check (struct xt_mtchk_param const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int recent_mt_check_v1(const struct xt_mtchk_param *par)
{
	return recent_mt_check(par, par->matchinfo);
}