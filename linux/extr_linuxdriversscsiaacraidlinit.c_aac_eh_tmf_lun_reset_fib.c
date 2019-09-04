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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct scsi_lun {int dummy; } ;
struct fib {int hbacmd_size; scalar_t__ hw_error_pa; scalar_t__ hw_fib_va; } ;
struct aac_hba_tm_req {void* error_length; void* error_ptr_lo; void* error_ptr_hi; scalar_t__ lun; int /*<<< orphan*/  it_nexus; int /*<<< orphan*/  tmf; } ;
struct aac_hba_map_info {int /*<<< orphan*/  rmw_nexus; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_ERROR_BUFFER_SIZE ; 
 int /*<<< orphan*/  HBA_IU_TYPE_SCSI_TM_REQ ; 
 int /*<<< orphan*/  HBA_TMF_LUN_RESET ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int_to_scsilun (int,struct scsi_lun*) ; 
 int /*<<< orphan*/  memset (struct aac_hba_tm_req*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u8 aac_eh_tmf_lun_reset_fib(struct aac_hba_map_info *info,
				   struct fib *fib, u64 tmf_lun)
{
	struct aac_hba_tm_req *tmf;
	u64 address;

	/* start a HBA_TMF_LUN_RESET TMF request */
	tmf = (struct aac_hba_tm_req *)fib->hw_fib_va;
	memset(tmf, 0, sizeof(*tmf));
	tmf->tmf = HBA_TMF_LUN_RESET;
	tmf->it_nexus = info->rmw_nexus;
	int_to_scsilun(tmf_lun, (struct scsi_lun *)tmf->lun);

	address = (u64)fib->hw_error_pa;
	tmf->error_ptr_hi = cpu_to_le32
		((u32)(address >> 32));
	tmf->error_ptr_lo = cpu_to_le32
		((u32)(address & 0xffffffff));
	tmf->error_length = cpu_to_le32(FW_ERROR_BUFFER_SIZE);
	fib->hbacmd_size = sizeof(*tmf);

	return HBA_IU_TYPE_SCSI_TM_REQ;
}