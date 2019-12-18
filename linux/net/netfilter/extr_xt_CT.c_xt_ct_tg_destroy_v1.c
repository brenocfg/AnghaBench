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
struct xt_tgdtor_param {int /*<<< orphan*/  targinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  xt_ct_tg_destroy (struct xt_tgdtor_param const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xt_ct_tg_destroy_v1(const struct xt_tgdtor_param *par)
{
	xt_ct_tg_destroy(par, par->targinfo);
}