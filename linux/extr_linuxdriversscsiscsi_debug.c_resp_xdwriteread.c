#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sg_mapping_iter {unsigned char* addr; int length; } ;
struct sdebug_dev_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct scsi_data_buffer {TYPE_1__ table; } ;
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  INSUFF_RES_ASC ; 
 int /*<<< orphan*/  INSUFF_RES_ASCQ ; 
 int SG_MITER_ATOMIC ; 
 int SG_MITER_TO_SG ; 
 int check_condition_result ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mk_sense_buffer (struct scsi_cmnd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_bufflen (struct scsi_cmnd*) ; 
 struct scsi_data_buffer* scsi_in (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sg_copy_to_buffer (struct scsi_cmnd*,unsigned char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sg_miter_next (struct sg_mapping_iter*) ; 
 int /*<<< orphan*/  sg_miter_start (struct sg_mapping_iter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_miter_stop (struct sg_mapping_iter*) ; 

__attribute__((used)) static int resp_xdwriteread(struct scsi_cmnd *scp, unsigned long long lba,
			    unsigned int num, struct sdebug_dev_info *devip)
{
	int j;
	unsigned char *kaddr, *buf;
	unsigned int offset;
	struct scsi_data_buffer *sdb = scsi_in(scp);
	struct sg_mapping_iter miter;

	/* better not to use temporary buffer. */
	buf = kzalloc(scsi_bufflen(scp), GFP_ATOMIC);
	if (!buf) {
		mk_sense_buffer(scp, ILLEGAL_REQUEST, INSUFF_RES_ASC,
				INSUFF_RES_ASCQ);
		return check_condition_result;
	}

	scsi_sg_copy_to_buffer(scp, buf, scsi_bufflen(scp));

	offset = 0;
	sg_miter_start(&miter, sdb->table.sgl, sdb->table.nents,
			SG_MITER_ATOMIC | SG_MITER_TO_SG);

	while (sg_miter_next(&miter)) {
		kaddr = miter.addr;
		for (j = 0; j < miter.length; j++)
			*(kaddr + j) ^= *(buf + offset + j);

		offset += miter.length;
	}
	sg_miter_stop(&miter);
	kfree(buf);

	return 0;
}