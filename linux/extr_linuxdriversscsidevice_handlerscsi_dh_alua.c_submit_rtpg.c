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
struct scsi_sense_hdr {int dummy; } ;
struct scsi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALUA_FAILOVER_RETRIES ; 
 int ALUA_FAILOVER_TIMEOUT ; 
 int ALUA_RTPG_EXT_HDR_UNSUPP ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int HZ ; 
 int MAINTENANCE_IN ; 
 int MAX_COMMAND_SIZE ; 
 int MI_EXT_HDR_PARAM_FMT ; 
 int MI_REPORT_TARGET_PGS ; 
 int REQ_FAILFAST_DEV ; 
 int REQ_FAILFAST_DRIVER ; 
 int REQ_FAILFAST_TRANSPORT ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  put_unaligned_be32 (int,int*) ; 
 int scsi_execute (struct scsi_device*,int*,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ *,struct scsi_sense_hdr*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int submit_rtpg(struct scsi_device *sdev, unsigned char *buff,
		       int bufflen, struct scsi_sense_hdr *sshdr, int flags)
{
	u8 cdb[MAX_COMMAND_SIZE];
	int req_flags = REQ_FAILFAST_DEV | REQ_FAILFAST_TRANSPORT |
		REQ_FAILFAST_DRIVER;

	/* Prepare the command. */
	memset(cdb, 0x0, MAX_COMMAND_SIZE);
	cdb[0] = MAINTENANCE_IN;
	if (!(flags & ALUA_RTPG_EXT_HDR_UNSUPP))
		cdb[1] = MI_REPORT_TARGET_PGS | MI_EXT_HDR_PARAM_FMT;
	else
		cdb[1] = MI_REPORT_TARGET_PGS;
	put_unaligned_be32(bufflen, &cdb[6]);

	return scsi_execute(sdev, cdb, DMA_FROM_DEVICE, buff, bufflen, NULL,
			sshdr, ALUA_FAILOVER_TIMEOUT * HZ,
			ALUA_FAILOVER_RETRIES, req_flags, 0, NULL);
}