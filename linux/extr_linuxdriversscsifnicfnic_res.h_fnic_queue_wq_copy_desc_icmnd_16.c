#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  void* u64 ;
typedef  void* u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct vnic_wq_copy {int dummy; } ;
struct TYPE_9__ {void* e_d_tov; void* r_a_tov; int /*<<< orphan*/  mss; int /*<<< orphan*/  d_id; scalar_t__ _resvd2; int /*<<< orphan*/  lun; void* data_len; int /*<<< orphan*/  scsi_cdb; void* flags; scalar_t__ _resvd1; void* pri_ta; void* crn; void* sense_addr; void* sgl_addr; void* sense_len; void* sgl_cnt; scalar_t__* _resvd0; void* special_req_flags; void* lunmap_id; } ;
struct TYPE_10__ {TYPE_4__ icmnd_16; } ;
struct TYPE_6__ {void* req_id; } ;
struct TYPE_7__ {TYPE_1__ u; } ;
struct TYPE_8__ {TYPE_2__ tag; scalar_t__ _resvd; scalar_t__ status; int /*<<< orphan*/  type; } ;
struct fcpio_host_req {TYPE_5__ u; TYPE_3__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDB_16 ; 
 int /*<<< orphan*/  FCPIO_ICMND_16 ; 
 void* LUN_ADDRESS ; 
 int /*<<< orphan*/  hton24 (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void**,void*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fcpio_host_req* vnic_wq_copy_next_desc (struct vnic_wq_copy*) ; 
 int /*<<< orphan*/  vnic_wq_copy_post (struct vnic_wq_copy*) ; 

__attribute__((used)) static inline void fnic_queue_wq_copy_desc_icmnd_16(struct vnic_wq_copy *wq,
						    u32 req_id,
						    u32 lunmap_id, u8 spl_flags,
						    u32 sgl_cnt, u32 sense_len,
						    u64 sgl_addr, u64 sns_addr,
						    u8 crn, u8 pri_ta,
						    u8 flags, u8 *scsi_cdb,
						    u8 cdb_len,
						    u32 data_len, u8 *lun,
						    u32 d_id, u16 mss,
						    u32 ratov, u32 edtov)
{
	struct fcpio_host_req *desc = vnic_wq_copy_next_desc(wq);

	desc->hdr.type = FCPIO_ICMND_16; /* enum fcpio_type */
	desc->hdr.status = 0;            /* header status entry */
	desc->hdr._resvd = 0;            /* reserved */
	desc->hdr.tag.u.req_id = req_id; /* id for this request */

	desc->u.icmnd_16.lunmap_id = lunmap_id; /* index into lunmap table */
	desc->u.icmnd_16.special_req_flags = spl_flags; /* exch req flags */
	desc->u.icmnd_16._resvd0[0] = 0;        /* reserved */
	desc->u.icmnd_16._resvd0[1] = 0;        /* reserved */
	desc->u.icmnd_16._resvd0[2] = 0;        /* reserved */
	desc->u.icmnd_16.sgl_cnt = sgl_cnt;     /* scatter-gather list count */
	desc->u.icmnd_16.sense_len = sense_len; /* sense buffer length */
	desc->u.icmnd_16.sgl_addr = sgl_addr;   /* scatter-gather list addr */
	desc->u.icmnd_16.sense_addr = sns_addr; /* sense buffer address */
	desc->u.icmnd_16.crn = crn;             /* SCSI Command Reference No.*/
	desc->u.icmnd_16.pri_ta = pri_ta; 	/* SCSI Pri & Task attribute */
	desc->u.icmnd_16._resvd1 = 0;           /* reserved: should be 0 */
	desc->u.icmnd_16.flags = flags;         /* command flags */
	memset(desc->u.icmnd_16.scsi_cdb, 0, CDB_16);
	memcpy(desc->u.icmnd_16.scsi_cdb, scsi_cdb, cdb_len);    /* SCSI CDB */
	desc->u.icmnd_16.data_len = data_len;   /* length of data expected */
	memcpy(desc->u.icmnd_16.lun, lun, LUN_ADDRESS);  /* LUN address */
	desc->u.icmnd_16._resvd2 = 0;          	/* reserved */
	hton24(desc->u.icmnd_16.d_id, d_id);	/* FC vNIC only: Target D_ID */
	desc->u.icmnd_16.mss = mss;            	/* FC vNIC only: max burst */
	desc->u.icmnd_16.r_a_tov = ratov; /*FC vNIC only: Res. Alloc Timeout */
	desc->u.icmnd_16.e_d_tov = edtov; /*FC vNIC only: Err Detect Timeout */

	vnic_wq_copy_post(wq);
}