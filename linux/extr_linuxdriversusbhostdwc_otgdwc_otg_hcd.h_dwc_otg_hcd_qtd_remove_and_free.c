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
typedef  int /*<<< orphan*/  dwc_otg_qh_t ;
typedef  int /*<<< orphan*/  dwc_otg_hcd_t ;

/* Variables and functions */
 int /*<<< orphan*/  dwc_otg_hcd_qtd_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc_otg_hcd_qtd_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void dwc_otg_hcd_qtd_remove_and_free(dwc_otg_hcd_t * hcd,
						   dwc_otg_qtd_t * qtd,
						   dwc_otg_qh_t * qh)
{
	dwc_otg_hcd_qtd_remove(hcd, qtd, qh);
	dwc_otg_hcd_qtd_free(qtd);
}