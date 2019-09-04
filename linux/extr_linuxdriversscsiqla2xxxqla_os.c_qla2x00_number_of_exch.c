#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_8__ {TYPE_1__* hw; } ;
typedef  TYPE_2__ scsi_qla_host_t ;
struct TYPE_7__ {scalar_t__ max_exchg; } ;

/* Variables and functions */
 scalar_t__ FW_DEF_EXCHANGES_CNT ; 
 scalar_t__ ql2xexchoffld ; 
 scalar_t__ ql2xiniexchg ; 
 scalar_t__ qla_dual_mode_enabled (TYPE_2__*) ; 
 scalar_t__ qla_ini_mode_enabled (TYPE_2__*) ; 
 scalar_t__ qla_tgt_mode_enabled (TYPE_2__*) ; 

__attribute__((used)) static void
qla2x00_number_of_exch(scsi_qla_host_t *vha, u32 *ret_cnt, u16 max_cnt)
{
	u32 temp;
	*ret_cnt = FW_DEF_EXCHANGES_CNT;

	if (max_cnt > vha->hw->max_exchg)
		max_cnt = vha->hw->max_exchg;

	if (qla_ini_mode_enabled(vha)) {
		if (ql2xiniexchg > max_cnt)
			ql2xiniexchg = max_cnt;

		if (ql2xiniexchg > FW_DEF_EXCHANGES_CNT)
			*ret_cnt = ql2xiniexchg;
	} else if (qla_tgt_mode_enabled(vha)) {
		if (ql2xexchoffld > max_cnt)
			ql2xexchoffld = max_cnt;

		if (ql2xexchoffld > FW_DEF_EXCHANGES_CNT)
			*ret_cnt = ql2xexchoffld;
	} else if (qla_dual_mode_enabled(vha)) {
		temp = ql2xiniexchg + ql2xexchoffld;
		if (temp > max_cnt) {
			ql2xiniexchg -= (temp - max_cnt)/2;
			ql2xexchoffld -= (((temp - max_cnt)/2) + 1);
			temp = max_cnt;
		}

		if (temp > FW_DEF_EXCHANGES_CNT)
			*ret_cnt = temp;
	}
}