#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  phase; } ;
struct scsi_cmnd {TYPE_3__ SCp; } ;
struct fib {TYPE_4__* dev; } ;
struct aac_query_mount {void* type; void* count; void* command; } ;
struct aac_mount {void* status; TYPE_1__* mnt; } ;
struct TYPE_6__ {int supported_options2; } ;
struct TYPE_8__ {TYPE_2__ supplement_adapter_info; } ;
struct TYPE_5__ {void* vol; scalar_t__ capacityhigh; } ;

/* Variables and functions */
 int AAC_OPTION_VARIABLE_BLOCK_SIZE ; 
 int /*<<< orphan*/  AAC_OWNER_FIRMWARE ; 
 scalar_t__ CT_NONE ; 
 int /*<<< orphan*/  ContainerCommand ; 
 int EINPROGRESS ; 
 scalar_t__ FT_FILESYS ; 
 int /*<<< orphan*/  FsaNormal ; 
 scalar_t__ ST_OK ; 
 scalar_t__ VM_NameServe64 ; 
 scalar_t__ VM_NameServeAllBlk ; 
 int /*<<< orphan*/  _aac_probe_container2 (void*,struct fib*) ; 
 int /*<<< orphan*/  aac_fib_init (struct fib*) ; 
 int aac_fib_send (int /*<<< orphan*/ ,struct fib*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  (*) (void*,struct fib*),void*) ; 
 int /*<<< orphan*/  aac_supports_2T (TYPE_4__*) ; 
 int /*<<< orphan*/  aac_valid_context (struct scsi_cmnd*,struct fib*) ; 
 void* cpu_to_le32 (scalar_t__) ; 
 scalar_t__ fib_data (struct fib*) ; 
 scalar_t__ le32_to_cpu (void*) ; 
 scalar_t__ scmd_id (struct scsi_cmnd*) ; 

__attribute__((used)) static void _aac_probe_container1(void * context, struct fib * fibptr)
{
	struct scsi_cmnd * scsicmd;
	struct aac_mount * dresp;
	struct aac_query_mount *dinfo;
	int status;

	dresp = (struct aac_mount *) fib_data(fibptr);
	if (!aac_supports_2T(fibptr->dev)) {
		dresp->mnt[0].capacityhigh = 0;
		if ((le32_to_cpu(dresp->status) == ST_OK) &&
			(le32_to_cpu(dresp->mnt[0].vol) != CT_NONE)) {
			_aac_probe_container2(context, fibptr);
			return;
		}
	}
	scsicmd = (struct scsi_cmnd *) context;

	if (!aac_valid_context(scsicmd, fibptr))
		return;

	aac_fib_init(fibptr);

	dinfo = (struct aac_query_mount *)fib_data(fibptr);

	if (fibptr->dev->supplement_adapter_info.supported_options2 &
	    AAC_OPTION_VARIABLE_BLOCK_SIZE)
		dinfo->command = cpu_to_le32(VM_NameServeAllBlk);
	else
		dinfo->command = cpu_to_le32(VM_NameServe64);

	dinfo->count = cpu_to_le32(scmd_id(scsicmd));
	dinfo->type = cpu_to_le32(FT_FILESYS);
	scsicmd->SCp.phase = AAC_OWNER_FIRMWARE;

	status = aac_fib_send(ContainerCommand,
			  fibptr,
			  sizeof(struct aac_query_mount),
			  FsaNormal,
			  0, 1,
			  _aac_probe_container2,
			  (void *) scsicmd);
	/*
	 *	Check that the command queued to the controller
	 */
	if (status < 0 && status != -EINPROGRESS) {
		/* Inherit results from VM_NameServe, if any */
		dresp->status = cpu_to_le32(ST_OK);
		_aac_probe_container2(context, fibptr);
	}
}