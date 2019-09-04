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
struct pmcraid_instance {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMCRAID_HCAM_CODE_CONFIG_CHANGE ; 
 int /*<<< orphan*/  PMCRAID_HCAM_CODE_LOG_DATA ; 
 int /*<<< orphan*/  pmcraid_send_hcam (struct pmcraid_instance*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pmcraid_register_hcams(struct pmcraid_instance *pinstance)
{
	pmcraid_send_hcam(pinstance, PMCRAID_HCAM_CODE_CONFIG_CHANGE);
	pmcraid_send_hcam(pinstance, PMCRAID_HCAM_CODE_LOG_DATA);
}