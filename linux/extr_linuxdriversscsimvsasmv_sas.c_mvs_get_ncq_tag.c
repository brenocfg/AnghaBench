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
typedef  int u32 ;
struct sas_task {struct ata_queued_cmd* uldd_task; } ;
struct TYPE_2__ {scalar_t__ command; } ;
struct ata_queued_cmd {int tag; TYPE_1__ tf; } ;

/* Variables and functions */
 scalar_t__ ATA_CMD_FPDMA_READ ; 
 scalar_t__ ATA_CMD_FPDMA_RECV ; 
 scalar_t__ ATA_CMD_FPDMA_SEND ; 
 scalar_t__ ATA_CMD_FPDMA_WRITE ; 
 scalar_t__ ATA_CMD_NCQ_NON_DATA ; 

__attribute__((used)) static u32 mvs_get_ncq_tag(struct sas_task *task, u32 *tag)
{
	struct ata_queued_cmd *qc = task->uldd_task;

	if (qc) {
		if (qc->tf.command == ATA_CMD_FPDMA_WRITE ||
		    qc->tf.command == ATA_CMD_FPDMA_READ ||
		    qc->tf.command == ATA_CMD_FPDMA_RECV ||
		    qc->tf.command == ATA_CMD_FPDMA_SEND ||
		    qc->tf.command == ATA_CMD_NCQ_NON_DATA) {
			*tag = qc->tag;
			return 1;
		}
	}

	return 0;
}