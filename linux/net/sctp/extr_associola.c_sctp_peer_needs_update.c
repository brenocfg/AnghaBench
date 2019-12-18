#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_3__* sk; } ;
struct sctp_association {int state; int /*<<< orphan*/  pathmtu; TYPE_2__ base; scalar_t__ a_rwnd; scalar_t__ rwnd; } ;
struct TYPE_4__ {int rwnd_upd_shift; } ;
struct net {TYPE_1__ sctp; } ;
struct TYPE_6__ {int sk_rcvbuf; } ;

/* Variables and functions */
#define  SCTP_STATE_ESTABLISHED 131 
#define  SCTP_STATE_SHUTDOWN_PENDING 130 
#define  SCTP_STATE_SHUTDOWN_RECEIVED 129 
#define  SCTP_STATE_SHUTDOWN_SENT 128 
 int /*<<< orphan*/  __u32 ; 
 scalar_t__ max_t (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct net* sock_net (TYPE_3__*) ; 

__attribute__((used)) static inline bool sctp_peer_needs_update(struct sctp_association *asoc)
{
	struct net *net = sock_net(asoc->base.sk);
	switch (asoc->state) {
	case SCTP_STATE_ESTABLISHED:
	case SCTP_STATE_SHUTDOWN_PENDING:
	case SCTP_STATE_SHUTDOWN_RECEIVED:
	case SCTP_STATE_SHUTDOWN_SENT:
		if ((asoc->rwnd > asoc->a_rwnd) &&
		    ((asoc->rwnd - asoc->a_rwnd) >= max_t(__u32,
			   (asoc->base.sk->sk_rcvbuf >> net->sctp.rwnd_upd_shift),
			   asoc->pathmtu)))
			return true;
		break;
	default:
		break;
	}
	return false;
}