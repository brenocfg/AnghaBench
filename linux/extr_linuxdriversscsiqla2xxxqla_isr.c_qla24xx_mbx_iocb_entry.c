#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct TYPE_8__ {int* in_mb; } ;
struct TYPE_9__ {TYPE_2__ mbx; } ;
struct srb_iocb {TYPE_3__ u; } ;
struct req_que {int dummy; } ;
struct mbx_24xx_entry {int* mb; } ;
struct TYPE_7__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* done ) (TYPE_4__*,int) ;TYPE_1__ u; } ;
typedef  TYPE_4__ srb_t ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int MBS_MASK ; 
 int le16_to_cpu (int) ; 
 size_t min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* qla2x00_get_sp_from_handle (int /*<<< orphan*/ *,char const*,struct req_que*,struct mbx_24xx_entry*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int) ; 

__attribute__((used)) static void
qla24xx_mbx_iocb_entry(scsi_qla_host_t *vha, struct req_que *req,
    struct mbx_24xx_entry *pkt)
{
	const char func[] = "MBX-IOCB2";
	srb_t *sp;
	struct srb_iocb *si;
	u16 sz, i;
	int res;

	sp = qla2x00_get_sp_from_handle(vha, func, req, pkt);
	if (!sp)
		return;

	si = &sp->u.iocb_cmd;
	sz = min(ARRAY_SIZE(pkt->mb), ARRAY_SIZE(sp->u.iocb_cmd.u.mbx.in_mb));

	for (i = 0; i < sz; i++)
		si->u.mbx.in_mb[i] = le16_to_cpu(pkt->mb[i]);

	res = (si->u.mbx.in_mb[0] & MBS_MASK);

	sp->done(sp, res);
}