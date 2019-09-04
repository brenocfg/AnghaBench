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
struct vscsiif_response {size_t rqid; } ;
struct vscsifrnt_info {TYPE_1__** shadow; int /*<<< orphan*/  shadow_free_bitmap; } ;
struct TYPE_2__ {scalar_t__ act; } ;

/* Variables and functions */
 scalar_t__ VSCSIIF_ACT_SCSI_CDB ; 
 size_t VSCSIIF_MAX_REQS ; 
 scalar_t__ WARN (int,char*,size_t) ; 
 int /*<<< orphan*/  scsifront_cdb_cmd_done (struct vscsifrnt_info*,struct vscsiif_response*) ; 
 int /*<<< orphan*/  scsifront_sync_cmd_done (struct vscsifrnt_info*,struct vscsiif_response*) ; 
 scalar_t__ test_bit (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scsifront_do_response(struct vscsifrnt_info *info,
				  struct vscsiif_response *ring_rsp)
{
	if (WARN(ring_rsp->rqid >= VSCSIIF_MAX_REQS ||
		 test_bit(ring_rsp->rqid, info->shadow_free_bitmap),
		 "illegal rqid %u returned by backend!\n", ring_rsp->rqid))
		return;

	if (info->shadow[ring_rsp->rqid]->act == VSCSIIF_ACT_SCSI_CDB)
		scsifront_cdb_cmd_done(info, ring_rsp);
	else
		scsifront_sync_cmd_done(info, ring_rsp);
}