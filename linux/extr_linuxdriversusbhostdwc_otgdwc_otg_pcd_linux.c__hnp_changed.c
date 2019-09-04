#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dwc_otg_pcd_t ;
struct TYPE_3__ {int /*<<< orphan*/  a_alt_hnp_support; int /*<<< orphan*/  a_hnp_support; int /*<<< orphan*/  b_hnp_enable; int /*<<< orphan*/  is_otg; } ;
struct TYPE_4__ {TYPE_1__ gadget; } ;

/* Variables and functions */
 TYPE_2__* gadget_wrapper ; 
 int /*<<< orphan*/  get_a_alt_hnp_support (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_a_hnp_support (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_b_hnp_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _hnp_changed(dwc_otg_pcd_t * pcd)
{

	if (!gadget_wrapper->gadget.is_otg)
		return 0;

	gadget_wrapper->gadget.b_hnp_enable = get_b_hnp_enable(pcd);
	gadget_wrapper->gadget.a_hnp_support = get_a_hnp_support(pcd);
	gadget_wrapper->gadget.a_alt_hnp_support = get_a_alt_hnp_support(pcd);
	return 0;
}