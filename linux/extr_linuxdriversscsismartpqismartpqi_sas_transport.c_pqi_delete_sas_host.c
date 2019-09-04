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
struct pqi_ctrl_info {int /*<<< orphan*/  sas_host; } ;

/* Variables and functions */
 int /*<<< orphan*/  pqi_free_sas_node (int /*<<< orphan*/ ) ; 

void pqi_delete_sas_host(struct pqi_ctrl_info *ctrl_info)
{
	pqi_free_sas_node(ctrl_info->sas_host);
}