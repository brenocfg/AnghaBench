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
struct lpfc_vport {scalar_t__ fc_npr_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  lpfc_can_disctmo (struct lpfc_vport*) ; 
 scalar_t__ lpfc_els_disc_plogi (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_end_rscn (struct lpfc_vport*) ; 

__attribute__((used)) static void
lpfc_rscn_disc(struct lpfc_vport *vport)
{
	lpfc_can_disctmo(vport);

	/* RSCN discovery */
	/* go thru NPR nodes and issue ELS PLOGIs */
	if (vport->fc_npr_cnt)
		if (lpfc_els_disc_plogi(vport))
			return;

	lpfc_end_rscn(vport);
}