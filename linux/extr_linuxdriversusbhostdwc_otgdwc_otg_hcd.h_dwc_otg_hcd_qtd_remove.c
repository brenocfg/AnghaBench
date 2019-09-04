#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dwc_otg_qtd_t ;
struct TYPE_3__ {int /*<<< orphan*/  qtd_list; } ;
typedef  TYPE_1__ dwc_otg_qh_t ;
typedef  int /*<<< orphan*/  dwc_otg_hcd_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_CIRCLEQ_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtd_list_entry ; 

__attribute__((used)) static inline void dwc_otg_hcd_qtd_remove(dwc_otg_hcd_t * hcd,
					  dwc_otg_qtd_t * qtd,
					  dwc_otg_qh_t * qh)
{
	DWC_CIRCLEQ_REMOVE(&qh->qtd_list, qtd, qtd_list_entry);
}