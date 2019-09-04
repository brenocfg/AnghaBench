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
struct TYPE_2__ {int /*<<< orphan*/  sgi; int /*<<< orphan*/  ch_offset; int /*<<< orphan*/  bwmode; int /*<<< orphan*/  ht_option; } ;
struct sta_info {TYPE_1__ htpriv; int /*<<< orphan*/  raid; int /*<<< orphan*/  qos_option; } ;
struct pkt_attrib {int ampdu_en; int retry_ctrl; int /*<<< orphan*/  sgi; int /*<<< orphan*/  ch_offset; int /*<<< orphan*/  bwmode; int /*<<< orphan*/  ht_en; int /*<<< orphan*/  raid; int /*<<< orphan*/  qos_en; scalar_t__ triggered; scalar_t__ eosp; scalar_t__ mdata; } ;

/* Variables and functions */

__attribute__((used)) static void update_attrib_phy_info(struct pkt_attrib *pattrib, struct sta_info *psta)
{
	/*if (psta->rtsen)
		pattrib->vcs_mode = RTS_CTS;
	else if (psta->cts2self)
		pattrib->vcs_mode = CTS_TO_SELF;
	else
		pattrib->vcs_mode = NONE_VCS;*/

	pattrib->mdata = 0;
	pattrib->eosp = 0;
	pattrib->triggered = 0;

	/* qos_en, ht_en, init rate, , bw, ch_offset, sgi */
	pattrib->qos_en = psta->qos_option;

	pattrib->raid = psta->raid;
	pattrib->ht_en = psta->htpriv.ht_option;
	pattrib->bwmode = psta->htpriv.bwmode;
	pattrib->ch_offset = psta->htpriv.ch_offset;
	pattrib->sgi = psta->htpriv.sgi;
	pattrib->ampdu_en = false;
	pattrib->retry_ctrl = false;
}