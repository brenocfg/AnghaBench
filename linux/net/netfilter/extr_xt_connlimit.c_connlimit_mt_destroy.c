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
struct xt_mtdtor_param {int /*<<< orphan*/  family; int /*<<< orphan*/  net; struct xt_connlimit_info* matchinfo; } ;
struct xt_connlimit_info {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  nf_conncount_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void connlimit_mt_destroy(const struct xt_mtdtor_param *par)
{
	const struct xt_connlimit_info *info = par->matchinfo;

	nf_conncount_destroy(par->net, par->family, info->data);
}