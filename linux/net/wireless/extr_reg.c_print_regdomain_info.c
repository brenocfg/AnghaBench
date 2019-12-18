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
struct ieee80211_regdomain {int /*<<< orphan*/ * alpha2; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_rd_rules (struct ieee80211_regdomain const*) ; 

__attribute__((used)) static void print_regdomain_info(const struct ieee80211_regdomain *rd)
{
	pr_debug("Regulatory domain: %c%c\n", rd->alpha2[0], rd->alpha2[1]);
	print_rd_rules(rd);
}