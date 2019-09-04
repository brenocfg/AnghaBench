#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qla_tgt_cmd {int conf_compl_supported; TYPE_1__* qpair; } ;
struct TYPE_2__ {scalar_t__ enable_explicit_conf; scalar_t__ enable_class_2; } ;

/* Variables and functions */

__attribute__((used)) static inline int qlt_need_explicit_conf(struct qla_tgt_cmd *cmd,
    int sending_sense)
{
	if (cmd->qpair->enable_class_2)
		return 0;

	if (sending_sense)
		return cmd->conf_compl_supported;
	else
		return cmd->qpair->enable_explicit_conf &&
                    cmd->conf_compl_supported;
}