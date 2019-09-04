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
struct qla_tgt_mgmt_cmd {int /*<<< orphan*/  free_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcm_qla2xxx_complete_mcmd ; 
 int /*<<< orphan*/  tcm_qla2xxx_free_wq ; 

__attribute__((used)) static void tcm_qla2xxx_free_mcmd(struct qla_tgt_mgmt_cmd *mcmd)
{
	INIT_WORK(&mcmd->free_work, tcm_qla2xxx_complete_mcmd);
	queue_work(tcm_qla2xxx_free_wq, &mcmd->free_work);
}