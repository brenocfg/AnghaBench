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
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FROM_XFER_BUF ; 
 int /*<<< orphan*/  rtsx_stor_access_xfer_buf (unsigned char*,unsigned int,struct scsi_cmnd*,unsigned int*,unsigned int*,int /*<<< orphan*/ ) ; 
 unsigned int scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,unsigned int) ; 

void rtsx_stor_get_xfer_buf(unsigned char *buffer,
			    unsigned int buflen, struct scsi_cmnd *srb)
{
	unsigned int index = 0, offset = 0;

	rtsx_stor_access_xfer_buf(buffer, buflen, srb, &index, &offset,
				  FROM_XFER_BUF);
	if (buflen < scsi_bufflen(srb))
		scsi_set_resid(srb, scsi_bufflen(srb) - buflen);
}