#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct sk_buff {int dummy; } ;
struct rxrpc_wire_header {int dummy; } ;
struct TYPE_16__ {int /*<<< orphan*/  serial; } ;
struct rxrpc_skb_priv {TYPE_6__ hdr; } ;
struct rxrpc_key_token {TYPE_7__* kad; } ;
struct TYPE_13__ {scalar_t__ security_level; TYPE_9__* key; } ;
struct TYPE_12__ {scalar_t__ epoch; scalar_t__ cid; } ;
struct rxrpc_connection {scalar_t__ security_ix; TYPE_5__* channels; TYPE_3__ params; TYPE_2__ proto; int /*<<< orphan*/  debug_id; } ;
struct TYPE_14__ {void** call_id; void* level; void* inc_nonce; void* securityIndex; void* cid; void* epoch; } ;
struct rxkad_response {TYPE_4__ encrypted; void* ticket_len; void* kvno; void* version; } ;
struct rxkad_challenge {int /*<<< orphan*/  min_level; int /*<<< orphan*/  nonce; int /*<<< orphan*/  version; } ;
typedef  int /*<<< orphan*/  challenge ;
struct TYPE_11__ {struct rxrpc_key_token** data; } ;
struct TYPE_18__ {TYPE_1__ payload; } ;
struct TYPE_17__ {scalar_t__ kvno; scalar_t__ ticket_len; } ;
struct TYPE_15__ {scalar_t__ call_counter; } ;

/* Variables and functions */
 int EACCES ; 
 int ENOMEM ; 
 int EPROTO ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ RXKADEXPIRED ; 
 scalar_t__ RXKADINCONSISTENCY ; 
 scalar_t__ RXKADLEVELFAIL ; 
 scalar_t__ RXKADPACKETSHORT ; 
 scalar_t__ RXKAD_VERSION ; 
 scalar_t__ RX_PROTOCOL_ERROR ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _proto (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 void* htonl (scalar_t__) ; 
 int /*<<< orphan*/  key_serial (TYPE_9__*) ; 
 int key_validate (TYPE_9__*) ; 
 int /*<<< orphan*/  kfree (struct rxkad_response*) ; 
 struct rxkad_response* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxkad_calc_response_checksum (struct rxkad_response*) ; 
 int rxkad_encrypt_response (struct rxrpc_connection*,struct rxkad_response*,TYPE_7__*) ; 
 int rxkad_send_response (struct rxrpc_connection*,TYPE_6__*,struct rxkad_response*,TYPE_7__*) ; 
 struct rxrpc_skb_priv* rxrpc_skb (struct sk_buff*) ; 
 scalar_t__ skb_copy_bits (struct sk_buff*,int,struct rxkad_challenge*,int) ; 
 int /*<<< orphan*/  trace_rxrpc_rx_eproto (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 char* tracepoint_string (char*) ; 

__attribute__((used)) static int rxkad_respond_to_challenge(struct rxrpc_connection *conn,
				      struct sk_buff *skb,
				      u32 *_abort_code)
{
	const struct rxrpc_key_token *token;
	struct rxkad_challenge challenge;
	struct rxkad_response *resp;
	struct rxrpc_skb_priv *sp = rxrpc_skb(skb);
	const char *eproto;
	u32 version, nonce, min_level, abort_code;
	int ret;

	_enter("{%d,%x}", conn->debug_id, key_serial(conn->params.key));

	eproto = tracepoint_string("chall_no_key");
	abort_code = RX_PROTOCOL_ERROR;
	if (!conn->params.key)
		goto protocol_error;

	abort_code = RXKADEXPIRED;
	ret = key_validate(conn->params.key);
	if (ret < 0)
		goto other_error;

	eproto = tracepoint_string("chall_short");
	abort_code = RXKADPACKETSHORT;
	if (skb_copy_bits(skb, sizeof(struct rxrpc_wire_header),
			  &challenge, sizeof(challenge)) < 0)
		goto protocol_error;

	version = ntohl(challenge.version);
	nonce = ntohl(challenge.nonce);
	min_level = ntohl(challenge.min_level);

	_proto("Rx CHALLENGE %%%u { v=%u n=%u ml=%u }",
	       sp->hdr.serial, version, nonce, min_level);

	eproto = tracepoint_string("chall_ver");
	abort_code = RXKADINCONSISTENCY;
	if (version != RXKAD_VERSION)
		goto protocol_error;

	abort_code = RXKADLEVELFAIL;
	ret = -EACCES;
	if (conn->params.security_level < min_level)
		goto other_error;

	token = conn->params.key->payload.data[0];

	/* build the response packet */
	resp = kzalloc(sizeof(struct rxkad_response), GFP_NOFS);
	if (!resp)
		return -ENOMEM;

	resp->version			= htonl(RXKAD_VERSION);
	resp->encrypted.epoch		= htonl(conn->proto.epoch);
	resp->encrypted.cid		= htonl(conn->proto.cid);
	resp->encrypted.securityIndex	= htonl(conn->security_ix);
	resp->encrypted.inc_nonce	= htonl(nonce + 1);
	resp->encrypted.level		= htonl(conn->params.security_level);
	resp->kvno			= htonl(token->kad->kvno);
	resp->ticket_len		= htonl(token->kad->ticket_len);
	resp->encrypted.call_id[0]	= htonl(conn->channels[0].call_counter);
	resp->encrypted.call_id[1]	= htonl(conn->channels[1].call_counter);
	resp->encrypted.call_id[2]	= htonl(conn->channels[2].call_counter);
	resp->encrypted.call_id[3]	= htonl(conn->channels[3].call_counter);

	/* calculate the response checksum and then do the encryption */
	rxkad_calc_response_checksum(resp);
	ret = rxkad_encrypt_response(conn, resp, token->kad);
	if (ret == 0)
		ret = rxkad_send_response(conn, &sp->hdr, resp, token->kad);
	kfree(resp);
	return ret;

protocol_error:
	trace_rxrpc_rx_eproto(NULL, sp->hdr.serial, eproto);
	ret = -EPROTO;
other_error:
	*_abort_code = abort_code;
	return ret;
}