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
struct xt_mtdtor_param {struct xt_hashlimit_mtinfo1* matchinfo; } ;
struct xt_hashlimit_mtinfo1 {int /*<<< orphan*/  hinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  htable_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hashlimit_mt_destroy_v1(const struct xt_mtdtor_param *par)
{
	const struct xt_hashlimit_mtinfo1 *info = par->matchinfo;

	htable_put(info->hinfo);
}