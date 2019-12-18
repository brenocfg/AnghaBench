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
union sctp_params {TYPE_2__* ext; TYPE_1__* p; } ;
struct sctp_paramhdr {int dummy; } ;
struct TYPE_8__ {int reconf_capable; int prsctp_capable; int auth_capable; int asconf_capable; int intl_capable; } ;
struct sctp_association {TYPE_4__ peer; TYPE_3__* ep; } ;
typedef  int __u16 ;
struct TYPE_7__ {int /*<<< orphan*/  intl_enable; int /*<<< orphan*/  asconf_enable; int /*<<< orphan*/  auth_enable; int /*<<< orphan*/  prsctp_enable; int /*<<< orphan*/  reconf_enable; } ;
struct TYPE_6__ {int* chunks; } ;
struct TYPE_5__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
#define  SCTP_CID_ASCONF 133 
#define  SCTP_CID_ASCONF_ACK 132 
#define  SCTP_CID_AUTH 131 
#define  SCTP_CID_FWD_TSN 130 
#define  SCTP_CID_I_DATA 129 
#define  SCTP_CID_RECONF 128 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sctp_process_ext_param(struct sctp_association *asoc,
				   union sctp_params param)
{
	__u16 num_ext = ntohs(param.p->length) - sizeof(struct sctp_paramhdr);
	int i;

	for (i = 0; i < num_ext; i++) {
		switch (param.ext->chunks[i]) {
		case SCTP_CID_RECONF:
			if (asoc->ep->reconf_enable)
				asoc->peer.reconf_capable = 1;
			break;
		case SCTP_CID_FWD_TSN:
			if (asoc->ep->prsctp_enable)
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
			if (asoc->ep->asconf_enable)
				asoc->peer.asconf_capable = 1;
			break;
		case SCTP_CID_I_DATA:
			if (asoc->ep->intl_enable)
				asoc->peer.intl_capable = 1;
			break;
		default:
			break;
		}
	}
}