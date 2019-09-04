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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct sgentry64 {int dummy; } ;
struct scsi_cmnd {int dummy; } ;
struct fib {TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  count; } ;
struct aac_read64 {TYPE_2__ sg; scalar_t__ flags; scalar_t__ pad; void* block; void* sector_count; void* cid; void* command; } ;
struct aac_fibhdr {int dummy; } ;
typedef  int /*<<< orphan*/  fib_callback ;
struct TYPE_3__ {int max_fib_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ContainerCommand64 ; 
 int /*<<< orphan*/  FsaNormal ; 
 int /*<<< orphan*/  VM_CtHostRead64 ; 
 long aac_build_sg64 (struct scsi_cmnd*,TYPE_2__*) ; 
 int /*<<< orphan*/  aac_fib_init (struct fib*) ; 
 int aac_fib_send (int /*<<< orphan*/ ,struct fib*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ fib_data (struct fib*) ; 
 scalar_t__ io_callback ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scmd_id (struct scsi_cmnd*) ; 

__attribute__((used)) static int aac_read_block64(struct fib * fib, struct scsi_cmnd * cmd, u64 lba, u32 count)
{
	u16 fibsize;
	struct aac_read64 *readcmd;
	long ret;

	aac_fib_init(fib);
	readcmd = (struct aac_read64 *) fib_data(fib);
	readcmd->command = cpu_to_le32(VM_CtHostRead64);
	readcmd->cid = cpu_to_le16(scmd_id(cmd));
	readcmd->sector_count = cpu_to_le16(count);
	readcmd->block = cpu_to_le32((u32)(lba&0xffffffff));
	readcmd->pad   = 0;
	readcmd->flags = 0;

	ret = aac_build_sg64(cmd, &readcmd->sg);
	if (ret < 0)
		return ret;
	fibsize = sizeof(struct aac_read64) +
		((le32_to_cpu(readcmd->sg.count) - 1) *
		 sizeof (struct sgentry64));
	BUG_ON (fibsize > (fib->dev->max_fib_size -
				sizeof(struct aac_fibhdr)));
	/*
	 *	Now send the Fib to the adapter
	 */
	return aac_fib_send(ContainerCommand64,
			  fib,
			  fibsize,
			  FsaNormal,
			  0, 1,
			  (fib_callback) io_callback,
			  (void *) cmd);
}