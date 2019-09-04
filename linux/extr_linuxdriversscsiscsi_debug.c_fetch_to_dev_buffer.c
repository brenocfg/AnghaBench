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
struct scsi_cmnd {scalar_t__ sc_data_direction; } ;

/* Variables and functions */
 scalar_t__ DMA_TO_DEVICE ; 
 scalar_t__ scsi_bidi_cmnd (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_bufflen (struct scsi_cmnd*) ; 
 int scsi_sg_copy_to_buffer (struct scsi_cmnd*,unsigned char*,int) ; 

__attribute__((used)) static int fetch_to_dev_buffer(struct scsi_cmnd *scp, unsigned char *arr,
			       int arr_len)
{
	if (!scsi_bufflen(scp))
		return 0;
	if (!(scsi_bidi_cmnd(scp) || scp->sc_data_direction == DMA_TO_DEVICE))
		return -1;

	return scsi_sg_copy_to_buffer(scp, arr, arr_len);
}