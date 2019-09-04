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
typedef  int u8 ;
struct bnep_session {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  pkt ;

/* Variables and functions */
#define  BNEP_CMD_NOT_UNDERSTOOD 134 
 int /*<<< orphan*/  BNEP_CONN_NOT_ALLOWED ; 
 int BNEP_CONTROL ; 
#define  BNEP_FILTER_MULTI_ADDR_RSP 133 
#define  BNEP_FILTER_MULTI_ADDR_SET 132 
#define  BNEP_FILTER_NET_TYPE_RSP 131 
#define  BNEP_FILTER_NET_TYPE_SET 130 
#define  BNEP_SETUP_CONN_REQ 129 
#define  BNEP_SETUP_CONN_RSP 128 
 int /*<<< orphan*/  BNEP_SETUP_RESPONSE ; 
 int /*<<< orphan*/  BNEP_SETUP_RSP_SENT ; 
 int /*<<< orphan*/  BNEP_SUCCESS ; 
 int bnep_ctrl_set_mcfilter (struct bnep_session*,void*,int) ; 
 int bnep_ctrl_set_netfilter (struct bnep_session*,void*,int) ; 
 int bnep_send (struct bnep_session*,int*,int) ; 
 int bnep_send_rsp (struct bnep_session*,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnep_rx_control(struct bnep_session *s, void *data, int len)
{
	u8  cmd = *(u8 *)data;
	int err = 0;

	data++;
	len--;

	switch (cmd) {
	case BNEP_CMD_NOT_UNDERSTOOD:
	case BNEP_SETUP_CONN_RSP:
	case BNEP_FILTER_NET_TYPE_RSP:
	case BNEP_FILTER_MULTI_ADDR_RSP:
		/* Ignore these for now */
		break;

	case BNEP_FILTER_NET_TYPE_SET:
		err = bnep_ctrl_set_netfilter(s, data, len);
		break;

	case BNEP_FILTER_MULTI_ADDR_SET:
		err = bnep_ctrl_set_mcfilter(s, data, len);
		break;

	case BNEP_SETUP_CONN_REQ:
		/* Successful response should be sent only once */
		if (test_bit(BNEP_SETUP_RESPONSE, &s->flags) &&
		    !test_and_set_bit(BNEP_SETUP_RSP_SENT, &s->flags))
			err = bnep_send_rsp(s, BNEP_SETUP_CONN_RSP,
					    BNEP_SUCCESS);
		else
			err = bnep_send_rsp(s, BNEP_SETUP_CONN_RSP,
					    BNEP_CONN_NOT_ALLOWED);
		break;

	default: {
			u8 pkt[3];
			pkt[0] = BNEP_CONTROL;
			pkt[1] = BNEP_CMD_NOT_UNDERSTOOD;
			pkt[2] = cmd;
			err = bnep_send(s, pkt, sizeof(pkt));
		}
		break;
	}

	return err;
}