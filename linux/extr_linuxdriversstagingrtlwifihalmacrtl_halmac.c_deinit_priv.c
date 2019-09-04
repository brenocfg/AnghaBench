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
struct rtl_halmac_indicator {int dummy; } ;
struct rtl_halmac {struct rtl_halmac_indicator* indicator; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct rtl_halmac_indicator*) ; 

__attribute__((used)) static void deinit_priv(struct rtl_halmac *halmac)
{
	struct rtl_halmac_indicator *indicator;

	indicator = halmac->indicator;
	halmac->indicator = NULL;
	kfree(indicator);
}