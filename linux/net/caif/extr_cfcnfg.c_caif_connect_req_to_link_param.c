#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct dev_info {int id; } ;
struct TYPE_23__ {int paramlen; int /*<<< orphan*/  params; int /*<<< orphan*/  name; } ;
struct TYPE_19__ {int /*<<< orphan*/  volume; } ;
struct TYPE_18__ {int /*<<< orphan*/  connid; } ;
struct TYPE_24__ {TYPE_8__ utility; TYPE_4__ rfm; TYPE_3__ datagram; } ;
struct cfctrl_link_param {int phyid; int endpoint; int chtype; void* linktype; TYPE_9__ u; scalar_t__ priority; } ;
struct cfcnfg {int dummy; } ;
struct TYPE_13__ {int service; int type; } ;
struct TYPE_21__ {int /*<<< orphan*/  service; } ;
struct TYPE_20__ {int /*<<< orphan*/  volume; int /*<<< orphan*/  connection_id; } ;
struct TYPE_17__ {int /*<<< orphan*/  connection_id; } ;
struct TYPE_16__ {int type; } ;
struct TYPE_14__ {TYPE_10__ dbg; TYPE_6__ util; TYPE_5__ rfm; TYPE_2__ dgm; TYPE_1__ at; } ;
struct TYPE_15__ {TYPE_11__ u; } ;
struct TYPE_22__ {int size; int /*<<< orphan*/  data; } ;
struct caif_connect_request {scalar_t__ ifindex; int link_selector; int protocol; TYPE_12__ sockaddr; TYPE_7__ param; scalar_t__ priority; } ;
typedef  enum cfcnfg_phy_preference { ____Placeholder_cfcnfg_phy_preference } cfcnfg_phy_preference ;

/* Variables and functions */
#define  CAIFPROTO_AT 135 
#define  CAIFPROTO_DATAGRAM 134 
#define  CAIFPROTO_DATAGRAM_LOOP 133 
#define  CAIFPROTO_DEBUG 132 
#define  CAIFPROTO_RFM 131 
#define  CAIFPROTO_UTIL 130 
#define  CAIF_LINK_HIGH_BANDW 129 
#define  CAIF_LINK_LOW_LATENCY 128 
 scalar_t__ CAIF_PRIO_MAX ; 
 void* CFCTRL_SRV_DATAGRAM ; 
 void* CFCTRL_SRV_DBG ; 
 void* CFCTRL_SRV_RFM ; 
 void* CFCTRL_SRV_UTIL ; 
 void* CFCTRL_SRV_VEI ; 
 int CFPHYPREF_HIGH_BW ; 
 int CFPHYPREF_LOW_LAT ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  caif_assert (int) ; 
 int cfcnfg_get_id_from_ifi (struct cfcnfg*,scalar_t__) ; 
 struct dev_info* cfcnfg_get_phyid (struct cfcnfg*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct cfctrl_link_param*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int caif_connect_req_to_link_param(struct cfcnfg *cnfg,
					  struct caif_connect_request *s,
					  struct cfctrl_link_param *l)
{
	struct dev_info *dev_info;
	enum cfcnfg_phy_preference pref;
	int res;

	memset(l, 0, sizeof(*l));
	/* In caif protocol low value is high priority */
	l->priority = CAIF_PRIO_MAX - s->priority + 1;

	if (s->ifindex != 0) {
		res = cfcnfg_get_id_from_ifi(cnfg, s->ifindex);
		if (res < 0)
			return res;
		l->phyid = res;
	} else {
		switch (s->link_selector) {
		case CAIF_LINK_HIGH_BANDW:
			pref = CFPHYPREF_HIGH_BW;
			break;
		case CAIF_LINK_LOW_LATENCY:
			pref = CFPHYPREF_LOW_LAT;
			break;
		default:
			return -EINVAL;
		}
		dev_info = cfcnfg_get_phyid(cnfg, pref);
		if (dev_info == NULL)
			return -ENODEV;
		l->phyid = dev_info->id;
	}
	switch (s->protocol) {
	case CAIFPROTO_AT:
		l->linktype = CFCTRL_SRV_VEI;
		l->endpoint = (s->sockaddr.u.at.type >> 2) & 0x3;
		l->chtype = s->sockaddr.u.at.type & 0x3;
		break;
	case CAIFPROTO_DATAGRAM:
		l->linktype = CFCTRL_SRV_DATAGRAM;
		l->chtype = 0x00;
		l->u.datagram.connid = s->sockaddr.u.dgm.connection_id;
		break;
	case CAIFPROTO_DATAGRAM_LOOP:
		l->linktype = CFCTRL_SRV_DATAGRAM;
		l->chtype = 0x03;
		l->endpoint = 0x00;
		l->u.datagram.connid = s->sockaddr.u.dgm.connection_id;
		break;
	case CAIFPROTO_RFM:
		l->linktype = CFCTRL_SRV_RFM;
		l->u.datagram.connid = s->sockaddr.u.rfm.connection_id;
		strlcpy(l->u.rfm.volume, s->sockaddr.u.rfm.volume,
			sizeof(l->u.rfm.volume));
		break;
	case CAIFPROTO_UTIL:
		l->linktype = CFCTRL_SRV_UTIL;
		l->endpoint = 0x00;
		l->chtype = 0x00;
		strlcpy(l->u.utility.name, s->sockaddr.u.util.service,
			sizeof(l->u.utility.name));
		caif_assert(sizeof(l->u.utility.name) > 10);
		l->u.utility.paramlen = s->param.size;
		if (l->u.utility.paramlen > sizeof(l->u.utility.params))
			l->u.utility.paramlen = sizeof(l->u.utility.params);

		memcpy(l->u.utility.params, s->param.data,
		       l->u.utility.paramlen);

		break;
	case CAIFPROTO_DEBUG:
		l->linktype = CFCTRL_SRV_DBG;
		l->endpoint = s->sockaddr.u.dbg.service;
		l->chtype = s->sockaddr.u.dbg.type;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}