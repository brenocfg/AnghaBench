#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sock {int dummy; } ;
struct l2tp_session {int recv_seq; int send_seq; int lns_mode; int debug; int /*<<< orphan*/  name; int /*<<< orphan*/  reorder_timeout; } ;

/* Variables and functions */
 int ENOPROTOOPT ; 
 int /*<<< orphan*/  L2TP_MSG_CONTROL ; 
#define  PPPOL2TP_SO_DEBUG 132 
#define  PPPOL2TP_SO_LNSMODE 131 
#define  PPPOL2TP_SO_RECVSEQ 130 
#define  PPPOL2TP_SO_REORDERTO 129 
#define  PPPOL2TP_SO_SENDSEQ 128 
 scalar_t__ jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2tp_info (struct l2tp_session*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pppol2tp_session_getsockopt(struct sock *sk,
				       struct l2tp_session *session,
				       int optname, int *val)
{
	int err = 0;

	switch (optname) {
	case PPPOL2TP_SO_RECVSEQ:
		*val = session->recv_seq;
		l2tp_info(session, L2TP_MSG_CONTROL,
			  "%s: get recv_seq=%d\n", session->name, *val);
		break;

	case PPPOL2TP_SO_SENDSEQ:
		*val = session->send_seq;
		l2tp_info(session, L2TP_MSG_CONTROL,
			  "%s: get send_seq=%d\n", session->name, *val);
		break;

	case PPPOL2TP_SO_LNSMODE:
		*val = session->lns_mode;
		l2tp_info(session, L2TP_MSG_CONTROL,
			  "%s: get lns_mode=%d\n", session->name, *val);
		break;

	case PPPOL2TP_SO_DEBUG:
		*val = session->debug;
		l2tp_info(session, L2TP_MSG_CONTROL, "%s: get debug=%d\n",
			  session->name, *val);
		break;

	case PPPOL2TP_SO_REORDERTO:
		*val = (int) jiffies_to_msecs(session->reorder_timeout);
		l2tp_info(session, L2TP_MSG_CONTROL,
			  "%s: get reorder_timeout=%d\n", session->name, *val);
		break;

	default:
		err = -ENOPROTOOPT;
	}

	return err;
}