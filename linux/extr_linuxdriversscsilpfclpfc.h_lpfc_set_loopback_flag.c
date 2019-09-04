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
struct lpfc_hba {scalar_t__ cfg_topology; int /*<<< orphan*/  link_flag; } ;

/* Variables and functions */
 scalar_t__ FLAGS_LOCAL_LB ; 
 int /*<<< orphan*/  LS_LOOPBACK_MODE ; 

__attribute__((used)) static inline void
lpfc_set_loopback_flag(struct lpfc_hba *phba)
{
	if (phba->cfg_topology == FLAGS_LOCAL_LB)
		phba->link_flag |= LS_LOOPBACK_MODE;
	else
		phba->link_flag &= ~LS_LOOPBACK_MODE;
}