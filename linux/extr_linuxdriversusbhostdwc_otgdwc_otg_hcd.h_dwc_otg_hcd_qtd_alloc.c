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
typedef  int /*<<< orphan*/  dwc_otg_qtd_t ;

/* Variables and functions */
 scalar_t__ DWC_ALLOC (int) ; 
 scalar_t__ DWC_ALLOC_ATOMIC (int) ; 

__attribute__((used)) static inline dwc_otg_qtd_t *dwc_otg_hcd_qtd_alloc(int atomic_alloc)
{
	if (atomic_alloc)
		return (dwc_otg_qtd_t *) DWC_ALLOC_ATOMIC(sizeof(dwc_otg_qtd_t));
	else
		return (dwc_otg_qtd_t *) DWC_ALLOC(sizeof(dwc_otg_qtd_t));
}