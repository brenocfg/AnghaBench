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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct l2cap_conn {int dummy; } ;
struct l2cap_conf_rsp {int /*<<< orphan*/  data; int /*<<< orphan*/  result; int /*<<< orphan*/  flags; int /*<<< orphan*/  scid; } ;
struct l2cap_conf_req {int dummy; } ;
struct l2cap_cmd_hdr {int /*<<< orphan*/  ident; } ;
struct l2cap_chan {scalar_t__ mode; int /*<<< orphan*/  conf_state; int /*<<< orphan*/  num_conf_req; int /*<<< orphan*/  num_conf_rsp; int /*<<< orphan*/  ident; int /*<<< orphan*/  hs_hcon; } ;
typedef  int /*<<< orphan*/  req ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int,int,int,int) ; 
 int /*<<< orphan*/  CONF_INPUT_DONE ; 
 int /*<<< orphan*/  CONF_LOC_CONF_PEND ; 
 int /*<<< orphan*/  CONF_OUTPUT_DONE ; 
 int /*<<< orphan*/  CONF_REM_CONF_PEND ; 
 int ECONNRESET ; 
 int EPROTO ; 
 int L2CAP_CONF_FLAG_CONTINUATION ; 
 int /*<<< orphan*/  L2CAP_CONF_MAX_CONF_RSP ; 
#define  L2CAP_CONF_PENDING 130 
 int /*<<< orphan*/  L2CAP_CONF_REQ ; 
#define  L2CAP_CONF_SUCCESS 129 
#define  L2CAP_CONF_UNACCEPT 128 
 int /*<<< orphan*/  L2CAP_DISC_REJ_TIMEOUT ; 
 scalar_t__ L2CAP_MODE_ERTM ; 
 scalar_t__ L2CAP_MODE_STREAMING ; 
 int __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_chan_timer (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amp_create_logical_link (struct l2cap_chan*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cap_chan_ready (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_chan_set_err (struct l2cap_chan*,int) ; 
 int /*<<< orphan*/  l2cap_chan_unlock (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_check_efs (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_conf_rfc_get (struct l2cap_chan*,int /*<<< orphan*/ ,int) ; 
 int l2cap_ertm_init (struct l2cap_chan*) ; 
 struct l2cap_chan* l2cap_get_chan_by_scid (struct l2cap_conn*,int) ; 
 int /*<<< orphan*/  l2cap_get_ident (struct l2cap_conn*) ; 
 int l2cap_parse_conf_rsp (struct l2cap_chan*,int /*<<< orphan*/ ,int,char*,int,int*) ; 
 int /*<<< orphan*/  l2cap_send_cmd (struct l2cap_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  l2cap_send_disconn_req (struct l2cap_chan*,int) ; 
 int /*<<< orphan*/  l2cap_send_efs_conf_rsp (struct l2cap_chan*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_default_fcs (struct l2cap_chan*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int l2cap_config_rsp(struct l2cap_conn *conn,
				   struct l2cap_cmd_hdr *cmd, u16 cmd_len,
				   u8 *data)
{
	struct l2cap_conf_rsp *rsp = (struct l2cap_conf_rsp *)data;
	u16 scid, flags, result;
	struct l2cap_chan *chan;
	int len = cmd_len - sizeof(*rsp);
	int err = 0;

	if (cmd_len < sizeof(*rsp))
		return -EPROTO;

	scid   = __le16_to_cpu(rsp->scid);
	flags  = __le16_to_cpu(rsp->flags);
	result = __le16_to_cpu(rsp->result);

	BT_DBG("scid 0x%4.4x flags 0x%2.2x result 0x%2.2x len %d", scid, flags,
	       result, len);

	chan = l2cap_get_chan_by_scid(conn, scid);
	if (!chan)
		return 0;

	switch (result) {
	case L2CAP_CONF_SUCCESS:
		l2cap_conf_rfc_get(chan, rsp->data, len);
		clear_bit(CONF_REM_CONF_PEND, &chan->conf_state);
		break;

	case L2CAP_CONF_PENDING:
		set_bit(CONF_REM_CONF_PEND, &chan->conf_state);

		if (test_bit(CONF_LOC_CONF_PEND, &chan->conf_state)) {
			char buf[64];

			len = l2cap_parse_conf_rsp(chan, rsp->data, len,
						   buf, sizeof(buf), &result);
			if (len < 0) {
				l2cap_send_disconn_req(chan, ECONNRESET);
				goto done;
			}

			if (!chan->hs_hcon) {
				l2cap_send_efs_conf_rsp(chan, buf, cmd->ident,
							0);
			} else {
				if (l2cap_check_efs(chan)) {
					amp_create_logical_link(chan);
					chan->ident = cmd->ident;
				}
			}
		}
		goto done;

	case L2CAP_CONF_UNACCEPT:
		if (chan->num_conf_rsp <= L2CAP_CONF_MAX_CONF_RSP) {
			char req[64];

			if (len > sizeof(req) - sizeof(struct l2cap_conf_req)) {
				l2cap_send_disconn_req(chan, ECONNRESET);
				goto done;
			}

			/* throw out any old stored conf requests */
			result = L2CAP_CONF_SUCCESS;
			len = l2cap_parse_conf_rsp(chan, rsp->data, len,
						   req, sizeof(req), &result);
			if (len < 0) {
				l2cap_send_disconn_req(chan, ECONNRESET);
				goto done;
			}

			l2cap_send_cmd(conn, l2cap_get_ident(conn),
				       L2CAP_CONF_REQ, len, req);
			chan->num_conf_req++;
			if (result != L2CAP_CONF_SUCCESS)
				goto done;
			break;
		}
		/* fall through */

	default:
		l2cap_chan_set_err(chan, ECONNRESET);

		__set_chan_timer(chan, L2CAP_DISC_REJ_TIMEOUT);
		l2cap_send_disconn_req(chan, ECONNRESET);
		goto done;
	}

	if (flags & L2CAP_CONF_FLAG_CONTINUATION)
		goto done;

	set_bit(CONF_INPUT_DONE, &chan->conf_state);

	if (test_bit(CONF_OUTPUT_DONE, &chan->conf_state)) {
		set_default_fcs(chan);

		if (chan->mode == L2CAP_MODE_ERTM ||
		    chan->mode == L2CAP_MODE_STREAMING)
			err = l2cap_ertm_init(chan);

		if (err < 0)
			l2cap_send_disconn_req(chan, -err);
		else
			l2cap_chan_ready(chan);
	}

done:
	l2cap_chan_unlock(chan);
	return err;
}