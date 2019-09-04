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
typedef  int u16 ;
struct sgmap64 {int dummy; } ;
struct sgentry64 {int dummy; } ;
struct sgentry {int dummy; } ;
struct scsi_cmnd {int /*<<< orphan*/  cmd_len; int /*<<< orphan*/  cmnd; } ;
struct fib {TYPE_2__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  count; } ;
struct aac_srb {TYPE_1__ sg; int /*<<< orphan*/  cdb; int /*<<< orphan*/  count; } ;
struct aac_fibhdr {int dummy; } ;
typedef  int /*<<< orphan*/  fib_callback ;
struct TYPE_4__ {int max_fib_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  FsaNormal ; 
 int /*<<< orphan*/  ScsiPortCommand64 ; 
 long aac_build_sg64 (struct scsi_cmnd*,struct sgmap64*) ; 
 int aac_fib_send (int /*<<< orphan*/ ,struct fib*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*) ; 
 struct aac_srb* aac_scsi_common (struct fib*,struct scsi_cmnd*) ; 
 scalar_t__ aac_srb_callback ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_bufflen (struct scsi_cmnd*) ; 

__attribute__((used)) static int aac_scsi_64(struct fib * fib, struct scsi_cmnd * cmd)
{
	u16 fibsize;
	struct aac_srb * srbcmd = aac_scsi_common(fib, cmd);
	long ret;

	ret = aac_build_sg64(cmd, (struct sgmap64 *) &srbcmd->sg);
	if (ret < 0)
		return ret;
	srbcmd->count = cpu_to_le32(scsi_bufflen(cmd));

	memset(srbcmd->cdb, 0, sizeof(srbcmd->cdb));
	memcpy(srbcmd->cdb, cmd->cmnd, cmd->cmd_len);
	/*
	 *	Build Scatter/Gather list
	 */
	fibsize = sizeof (struct aac_srb) - sizeof (struct sgentry) +
		((le32_to_cpu(srbcmd->sg.count) & 0xff) *
		 sizeof (struct sgentry64));
	BUG_ON (fibsize > (fib->dev->max_fib_size -
				sizeof(struct aac_fibhdr)));

	/*
	 *	Now send the Fib to the adapter
	 */
	return aac_fib_send(ScsiPortCommand64, fib,
				fibsize, FsaNormal, 0, 1,
				  (fib_callback) aac_srb_callback,
				  (void *) cmd);
}