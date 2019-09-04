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
struct xt_mtchk_param {struct xt_esp* matchinfo; } ;
struct xt_esp {int invflags; } ;

/* Variables and functions */
 int EINVAL ; 
 int XT_ESP_INV_MASK ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static int esp_mt_check(const struct xt_mtchk_param *par)
{
	const struct xt_esp *espinfo = par->matchinfo;

	if (espinfo->invflags & ~XT_ESP_INV_MASK) {
		pr_debug("unknown flags %X\n", espinfo->invflags);
		return -EINVAL;
	}

	return 0;
}