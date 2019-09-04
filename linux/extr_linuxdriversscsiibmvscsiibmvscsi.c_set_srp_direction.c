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
typedef  int u8 ;
struct srp_cmd {int data_out_desc_cnt; int data_in_desc_cnt; int buf_fmt; } ;
struct scsi_cmnd {scalar_t__ sc_data_direction; } ;

/* Variables and functions */
 scalar_t__ DMA_TO_DEVICE ; 
 int /*<<< orphan*/  MAX_INDIRECT_BUFS ; 
 int SRP_DATA_DESC_DIRECT ; 
 int SRP_DATA_DESC_INDIRECT ; 
 int min (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_srp_direction(struct scsi_cmnd *cmd,
			      struct srp_cmd *srp_cmd, 
			      int numbuf)
{
	u8 fmt;

	if (numbuf == 0)
		return;
	
	if (numbuf == 1)
		fmt = SRP_DATA_DESC_DIRECT;
	else {
		fmt = SRP_DATA_DESC_INDIRECT;
		numbuf = min(numbuf, MAX_INDIRECT_BUFS);

		if (cmd->sc_data_direction == DMA_TO_DEVICE)
			srp_cmd->data_out_desc_cnt = numbuf;
		else
			srp_cmd->data_in_desc_cnt = numbuf;
	}

	if (cmd->sc_data_direction == DMA_TO_DEVICE)
		srp_cmd->buf_fmt = fmt << 4;
	else
		srp_cmd->buf_fmt = fmt;
}