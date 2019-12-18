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
struct rxrpc_key_token {TYPE_2__* kad; int /*<<< orphan*/  security_index; } ;
struct TYPE_7__ {int security_level; TYPE_4__* key; } ;
struct rxrpc_connection {int size_align; int security_size; struct crypto_sync_skcipher* cipher; TYPE_3__ params; int /*<<< orphan*/  security_ix; int /*<<< orphan*/  debug_id; } ;
struct rxkad_level2_hdr {int dummy; } ;
struct rxkad_level1_hdr {int dummy; } ;
struct crypto_sync_skcipher {int dummy; } ;
struct TYPE_5__ {struct rxrpc_key_token** data; } ;
struct TYPE_8__ {TYPE_1__ payload; } ;
struct TYPE_6__ {int /*<<< orphan*/  session_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EKEYREJECTED ; 
 scalar_t__ IS_ERR (struct crypto_sync_skcipher*) ; 
 int PTR_ERR (struct crypto_sync_skcipher*) ; 
#define  RXRPC_SECURITY_AUTH 130 
#define  RXRPC_SECURITY_ENCRYPT 129 
#define  RXRPC_SECURITY_PLAIN 128 
 int /*<<< orphan*/  _debug (char*) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 struct crypto_sync_skcipher* crypto_alloc_sync_skcipher (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_sync_skcipher_setkey (struct crypto_sync_skcipher*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  key_serial (TYPE_4__*) ; 

__attribute__((used)) static int rxkad_init_connection_security(struct rxrpc_connection *conn)
{
	struct crypto_sync_skcipher *ci;
	struct rxrpc_key_token *token;
	int ret;

	_enter("{%d},{%x}", conn->debug_id, key_serial(conn->params.key));

	token = conn->params.key->payload.data[0];
	conn->security_ix = token->security_index;

	ci = crypto_alloc_sync_skcipher("pcbc(fcrypt)", 0, 0);
	if (IS_ERR(ci)) {
		_debug("no cipher");
		ret = PTR_ERR(ci);
		goto error;
	}

	if (crypto_sync_skcipher_setkey(ci, token->kad->session_key,
				   sizeof(token->kad->session_key)) < 0)
		BUG();

	switch (conn->params.security_level) {
	case RXRPC_SECURITY_PLAIN:
		break;
	case RXRPC_SECURITY_AUTH:
		conn->size_align = 8;
		conn->security_size = sizeof(struct rxkad_level1_hdr);
		break;
	case RXRPC_SECURITY_ENCRYPT:
		conn->size_align = 8;
		conn->security_size = sizeof(struct rxkad_level2_hdr);
		break;
	default:
		ret = -EKEYREJECTED;
		goto error;
	}

	conn->cipher = ci;
	ret = 0;
error:
	_leave(" = %d", ret);
	return ret;
}