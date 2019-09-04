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
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_vport {int dummy; } ;
struct lpfc_nodelist {int /*<<< orphan*/  nlp_state; } ;

/* Variables and functions */

__attribute__((used)) static uint32_t
lpfc_device_recov_logo_issue(struct lpfc_vport *vport,
			     struct lpfc_nodelist *ndlp,
			     void *arg, uint32_t evt)
{
	/*
	 * Device Recovery events have no meaning for a node with a LOGO
	 * outstanding.  The LOGO has to complete first and handle the
	 * node from that point.
	 */
	return ndlp->nlp_state;
}