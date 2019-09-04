#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int command; } ;
struct TYPE_4__ {TYPE_1__ fis; } ;
struct sas_task {TYPE_2__ ata_task; } ;

/* Variables and functions */
#define  ATA_CMD_FPDMA_READ 137 
#define  ATA_CMD_FPDMA_WRITE 136 
#define  ATA_CMD_PIO_READ 135 
#define  ATA_CMD_PIO_READ_EXT 134 
#define  ATA_CMD_PIO_WRITE 133 
#define  ATA_CMD_PIO_WRITE_EXT 132 
#define  ATA_CMD_READ 131 
#define  ATA_CMD_READ_EXT 130 
#define  ATA_CMD_WRITE 129 
#define  ATA_CMD_WRITE_EXT 128 

__attribute__((used)) static int check_enc_sat_cmd(struct sas_task *task)
{
	int ret = 0;
	switch (task->ata_task.fis.command) {
	case ATA_CMD_FPDMA_READ:
	case ATA_CMD_READ_EXT:
	case ATA_CMD_READ:
	case ATA_CMD_FPDMA_WRITE:
	case ATA_CMD_WRITE_EXT:
	case ATA_CMD_WRITE:
	case ATA_CMD_PIO_READ:
	case ATA_CMD_PIO_READ_EXT:
	case ATA_CMD_PIO_WRITE:
	case ATA_CMD_PIO_WRITE_EXT:
		ret = 1;
		break;
	default:
		ret = 0;
		break;
	}
	return ret;
}