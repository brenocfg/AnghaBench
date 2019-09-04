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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct TYPE_5__ {scalar_t__ area; scalar_t__ domain; scalar_t__ al_pa; } ;
struct TYPE_6__ {TYPE_1__ b; } ;
struct scsi_qla_host {TYPE_4__* hw; TYPE_2__ d_id; } ;
struct TYPE_7__ {int /*<<< orphan*/  host_map; } ;
struct TYPE_8__ {TYPE_3__ tgt; } ;

/* Variables and functions */
 struct scsi_qla_host* btree_lookup32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ql_dbg (scalar_t__,struct scsi_qla_host*,int,char*,int) ; 
 scalar_t__ ql_dbg_tgt_mgt ; 
 scalar_t__ ql_dbg_verbose ; 

__attribute__((used)) static inline
struct scsi_qla_host *qlt_find_host_by_d_id(struct scsi_qla_host *vha,
	uint8_t *d_id)
{
	struct scsi_qla_host *host;
	uint32_t key = 0;

	if ((vha->d_id.b.area == d_id[1]) && (vha->d_id.b.domain == d_id[0]) &&
	    (vha->d_id.b.al_pa == d_id[2]))
		return vha;

	key  = (uint32_t)d_id[0] << 16;
	key |= (uint32_t)d_id[1] <<  8;
	key |= (uint32_t)d_id[2];

	host = btree_lookup32(&vha->hw->tgt.host_map, key);
	if (!host)
		ql_dbg(ql_dbg_tgt_mgt + ql_dbg_verbose, vha, 0xf005,
		    "Unable to find host %06x\n", key);

	return host;
}