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
struct TYPE_4__ {TYPE_1__ tcp; } ;
struct nf_conn {TYPE_2__ proto; } ;

/* Variables and functions */
#define  TCP_CONNTRACK_CLOSE 132 
#define  TCP_CONNTRACK_CLOSE_WAIT 131 
#define  TCP_CONNTRACK_FIN_WAIT 130 
#define  TCP_CONNTRACK_LAST_ACK 129 
#define  TCP_CONNTRACK_TIME_WAIT 128 

__attribute__((used)) static bool tcp_can_early_drop(const struct nf_conn *ct)
{
	switch (ct->proto.tcp.state) {
	case TCP_CONNTRACK_FIN_WAIT:
	case TCP_CONNTRACK_LAST_ACK:
	case TCP_CONNTRACK_TIME_WAIT:
	case TCP_CONNTRACK_CLOSE:
	case TCP_CONNTRACK_CLOSE_WAIT:
		return true;
	default:
		break;
	}

	return false;
}