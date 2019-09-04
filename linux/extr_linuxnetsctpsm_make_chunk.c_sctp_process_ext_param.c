#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
union sctp_params {TYPE_2__* ext; TYPE_1__* p; } ;
struct sctp_paramhdr {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/  sk; } ;
struct TYPE_12__ {int reconf_capable; int prsctp_capable; int auth_capable; int asconf_capable; } ;
struct sctp_association {int intl_enable; TYPE_6__ base; TYPE_5__ peer; TYPE_3__* ep; int /*<<< orphan*/  prsctp_enable; int /*<<< orphan*/  reconf_enable; } ;
struct TYPE_11__ {int /*<<< orphan*/  addip_enable; } ;
struct net {TYPE_4__ sctp; } ;
typedef  int __u16 ;
struct TYPE_14__ {int /*<<< orphan*/  strm_interleave; } ;
struct TYPE_10__ {int /*<<< orphan*/  auth_enable; } ;
struct TYPE_9__ {int* chunks; } ;
struct TYPE_8__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
#define  SCTP_CID_ASCONF 133 
#define  SCTP_CID_ASCONF_ACK 132 
#define  SCTP_CID_AUTH 131 
#define  SCTP_CID_FWD_TSN 130 
#define  SCTP_CID_I_DATA 129 
#define  SCTP_CID_RECONF 128 
 int ntohs (int /*<<< orphan*/ ) ; 
 TYPE_7__* sctp_sk (int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sctp_process_ext_param(struct sctp_association *asoc,
				   union sctp_params param)
{
	__u16 num_ext = ntohs(param.p->length) - sizeof(struct sctp_paramhdr);
	struct net *net = sock_net(asoc->base.sk);
	int i;

	for (i = 0; i < num_ext; i++) {
		switch (param.ext->chunks[i]) {
		case SCTP_CID_RECONF:
			if (asoc->reconf_enable &&
			    !asoc->peer.reconf_capable)
				asoc->peer.reconf_capable = 1;
			break;
		case SCTP_CID_FWD_TSN:
			if (asoc->prsctp_enable && !asoc->peer.prsctp_capable)
				asoc->peer.prsctp_capable = 1;
			break;
		case SCTP_CID_AUTH:
			/* if the peer reports AUTH, assume that he
			 * supports AUTH.
			 */
			if (asoc->ep->auth_enable)
				asoc->peer.auth_capable = 1;
			break;
		case SCTP_CID_ASCONF:
		case SCTP_CID_ASCONF_ACK:
			if (net->sctp.addip_enable)
				asoc->peer.asconf_capable = 1;
			break;
		case SCTP_CID_I_DATA:
			if (sctp_sk(asoc->base.sk)->strm_interleave)
				asoc->intl_enable = 1;
			break;
		default:
			break;
		}
	}
}