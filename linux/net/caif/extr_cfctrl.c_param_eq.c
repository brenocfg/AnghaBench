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
struct TYPE_9__ {int /*<<< orphan*/  connid; } ;
struct TYPE_8__ {int /*<<< orphan*/  paramlen; int /*<<< orphan*/  params; int /*<<< orphan*/  name; int /*<<< orphan*/  fifosize_bufs; int /*<<< orphan*/  fifosize_kb; } ;
struct TYPE_7__ {int /*<<< orphan*/  volume; int /*<<< orphan*/  connid; } ;
struct TYPE_6__ {int /*<<< orphan*/  connid; } ;
struct TYPE_10__ {TYPE_4__ video; TYPE_3__ utility; TYPE_2__ rfm; TYPE_1__ datagram; } ;
struct cfctrl_link_param {int linktype; scalar_t__ priority; scalar_t__ phyid; scalar_t__ endpoint; scalar_t__ chtype; TYPE_5__ u; } ;

/* Variables and functions */
#define  CFCTRL_SRV_DATAGRAM 134 
#define  CFCTRL_SRV_DBG 133 
#define  CFCTRL_SRV_DECM 132 
#define  CFCTRL_SRV_RFM 131 
#define  CFCTRL_SRV_UTIL 130 
#define  CFCTRL_SRV_VEI 129 
#define  CFCTRL_SRV_VIDEO 128 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool param_eq(const struct cfctrl_link_param *p1,
		     const struct cfctrl_link_param *p2)
{
	bool eq =
	    p1->linktype == p2->linktype &&
	    p1->priority == p2->priority &&
	    p1->phyid == p2->phyid &&
	    p1->endpoint == p2->endpoint && p1->chtype == p2->chtype;

	if (!eq)
		return false;

	switch (p1->linktype) {
	case CFCTRL_SRV_VEI:
		return true;
	case CFCTRL_SRV_DATAGRAM:
		return p1->u.datagram.connid == p2->u.datagram.connid;
	case CFCTRL_SRV_RFM:
		return
		    p1->u.rfm.connid == p2->u.rfm.connid &&
		    strcmp(p1->u.rfm.volume, p2->u.rfm.volume) == 0;
	case CFCTRL_SRV_UTIL:
		return
		    p1->u.utility.fifosize_kb == p2->u.utility.fifosize_kb
		    && p1->u.utility.fifosize_bufs ==
		    p2->u.utility.fifosize_bufs
		    && strcmp(p1->u.utility.name, p2->u.utility.name) == 0
		    && p1->u.utility.paramlen == p2->u.utility.paramlen
		    && memcmp(p1->u.utility.params, p2->u.utility.params,
			      p1->u.utility.paramlen) == 0;

	case CFCTRL_SRV_VIDEO:
		return p1->u.video.connid == p2->u.video.connid;
	case CFCTRL_SRV_DBG:
		return true;
	case CFCTRL_SRV_DECM:
		return false;
	default:
		return false;
	}
	return false;
}