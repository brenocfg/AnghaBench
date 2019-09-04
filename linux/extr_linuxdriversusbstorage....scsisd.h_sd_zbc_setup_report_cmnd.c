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
 int BLKPREP_INVALID ; 

__attribute__((used)) static inline int sd_zbc_setup_report_cmnd(struct scsi_cmnd *cmd)
{
	return BLKPREP_INVALID;
}