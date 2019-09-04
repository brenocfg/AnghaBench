#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int state; } ;
struct TYPE_4__ {TYPE_1__ sctp; } ;
struct nf_conn {TYPE_2__ proto; } ;

/* Variables and functions */
#define  SCTP_CONNTRACK_SHUTDOWN_ACK_SENT 130 
#define  SCTP_CONNTRACK_SHUTDOWN_RECD 129 
#define  SCTP_CONNTRACK_SHUTDOWN_SENT 128 

__attribute__((used)) static bool sctp_can_early_drop(const struct nf_conn *ct)
{
	switch (ct->proto.sctp.state) {
	case SCTP_CONNTRACK_SHUTDOWN_SENT:
	case SCTP_CONNTRACK_SHUTDOWN_RECD:
	case SCTP_CONNTRACK_SHUTDOWN_ACK_SENT:
		return true;
	default:
		break;
	}

	return false;
}