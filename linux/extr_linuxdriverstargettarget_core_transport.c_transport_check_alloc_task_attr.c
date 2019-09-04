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
struct se_device {TYPE_1__* transport; } ;
struct se_cmd {scalar_t__ sam_task_attr; struct se_device* se_dev; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;
struct TYPE_2__ {int transport_flags; } ;

/* Variables and functions */
 scalar_t__ TCM_ACA_TAG ; 
 int /*<<< orphan*/  TCM_INVALID_CDB_FIELD ; 
 int TRANSPORT_FLAG_PASSTHROUGH ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static sense_reason_t
transport_check_alloc_task_attr(struct se_cmd *cmd)
{
	struct se_device *dev = cmd->se_dev;

	/*
	 * Check if SAM Task Attribute emulation is enabled for this
	 * struct se_device storage object
	 */
	if (dev->transport->transport_flags & TRANSPORT_FLAG_PASSTHROUGH)
		return 0;

	if (cmd->sam_task_attr == TCM_ACA_TAG) {
		pr_debug("SAM Task Attribute ACA"
			" emulation is not supported\n");
		return TCM_INVALID_CDB_FIELD;
	}

	return 0;
}