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
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;} ;
struct fib {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int COMMAND_COMPLETE ; 
 int DID_OK ; 
 int SAM_STAT_GOOD ; 
 int /*<<< orphan*/  aac_fib_complete (struct fib*) ; 
 int /*<<< orphan*/  aac_fib_free (struct fib*) ; 
 int /*<<< orphan*/  aac_valid_context (struct scsi_cmnd*,struct fib*) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static void aac_start_stop_callback(void *context, struct fib *fibptr)
{
	struct scsi_cmnd *scsicmd = context;

	if (!aac_valid_context(scsicmd, fibptr))
		return;

	BUG_ON(fibptr == NULL);

	scsicmd->result = DID_OK << 16 | COMMAND_COMPLETE << 8 | SAM_STAT_GOOD;

	aac_fib_complete(fibptr);
	aac_fib_free(fibptr);
	scsicmd->scsi_done(scsicmd);
}