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
typedef  int u32 ;
typedef  int u16 ;
struct sgentry {int dummy; } ;
struct scsi_cmnd {int dummy; } ;
struct fib {struct aac_dev* dev; } ;
struct TYPE_4__ {void* count; } ;
struct aac_write {TYPE_2__ sg; void* count; void* block; void* cid; void* command; } ;
struct aac_fibhdr {int dummy; } ;
struct aac_dev {int max_fib_size; TYPE_1__* fsa_dev; } ;
typedef  int /*<<< orphan*/  fib_callback ;
struct TYPE_3__ {int block_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ContainerCommand ; 
 int /*<<< orphan*/  FsaNormal ; 
 int VM_CtBlockWrite ; 
 long aac_build_sg (struct scsi_cmnd*,TYPE_2__*) ; 
 int /*<<< orphan*/  aac_fib_init (struct fib*) ; 
 int aac_fib_send (int /*<<< orphan*/ ,struct fib*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*) ; 
 void* cpu_to_le32 (int) ; 
 scalar_t__ fib_data (struct fib*) ; 
 scalar_t__ io_callback ; 
 int le32_to_cpu (void*) ; 
 size_t scmd_id (struct scsi_cmnd*) ; 

__attribute__((used)) static int aac_write_block(struct fib * fib, struct scsi_cmnd * cmd, u64 lba, u32 count, int fua)
{
	u16 fibsize;
	struct aac_write *writecmd;
	struct aac_dev *dev = fib->dev;
	long ret;

	aac_fib_init(fib);
	writecmd = (struct aac_write *) fib_data(fib);
	writecmd->command = cpu_to_le32(VM_CtBlockWrite);
	writecmd->cid = cpu_to_le32(scmd_id(cmd));
	writecmd->block = cpu_to_le32((u32)(lba&0xffffffff));
	writecmd->count = cpu_to_le32(count *
		dev->fsa_dev[scmd_id(cmd)].block_size);
	writecmd->sg.count = cpu_to_le32(1);
	/* ->stable is not used - it did mean which type of write */

	ret = aac_build_sg(cmd, &writecmd->sg);
	if (ret < 0)
		return ret;
	fibsize = sizeof(struct aac_write) +
		((le32_to_cpu(writecmd->sg.count) - 1) *
		 sizeof (struct sgentry));
	BUG_ON (fibsize > (fib->dev->max_fib_size -
				sizeof(struct aac_fibhdr)));
	/*
	 *	Now send the Fib to the adapter
	 */
	return aac_fib_send(ContainerCommand,
			  fib,
			  fibsize,
			  FsaNormal,
			  0, 1,
			  (fib_callback) io_callback,
			  (void *) cmd);
}