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
typedef  int /*<<< orphan*/  uint8_t ;
struct nn_ws_handshake {char* opening_hs; char* resource; char* remote_host; int /*<<< orphan*/  usock; TYPE_3__* pipebase; int /*<<< orphan*/  expected_accept_key; } ;
struct nn_iovec {char* iov_base; void* iov_len; } ;
typedef  int /*<<< orphan*/  rand_key ;
typedef  int /*<<< orphan*/  encoded_key ;
struct TYPE_8__ {scalar_t__ client; char* ws_sp; } ;
struct TYPE_7__ {TYPE_2__* sock; } ;
struct TYPE_6__ {TYPE_1__* socktype; } ;
struct TYPE_5__ {scalar_t__ protocol; } ;

/* Variables and functions */
 int NN_WS_HANDSHAKE_ACCEPT_KEY_LEN ; 
 TYPE_4__* NN_WS_HANDSHAKE_SP_MAP ; 
 unsigned int NN_WS_HANDSHAKE_SP_MAP_LEN ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int nn_base64_encode (int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/  nn_random_generate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nn_usock_send (int /*<<< orphan*/ ,struct nn_iovec*,int) ; 
 int nn_ws_handshake_hash_key (char*,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,char*,char*) ; 
 void* strlen (char*) ; 

__attribute__((used)) static void nn_ws_handshake_client_request (struct nn_ws_handshake *self)
{
    struct nn_iovec open_request;
    size_t encoded_key_len;
    int rc;
    unsigned i;

    /*  Generate random 16-byte key as per RFC 6455 4.1 */
    uint8_t rand_key [16];

    /*  Known length required to base64 encode above random key plus
        string NULL terminator. */
    char encoded_key [24 + 1];

    nn_random_generate (rand_key, sizeof (rand_key));

    rc = nn_base64_encode (rand_key, sizeof (rand_key),
        encoded_key, sizeof (encoded_key));
    nn_assert (rc >=0);

    encoded_key_len = strlen (encoded_key);

    nn_assert (encoded_key_len == sizeof (encoded_key) - 1);

    /*  Pre-calculated expected Accept Key value as per
        RFC 6455 section 4.2.2.5.4 (version December 2011). */
    rc = nn_ws_handshake_hash_key (encoded_key, encoded_key_len,
        self->expected_accept_key, sizeof (self->expected_accept_key));

    nn_assert (rc == NN_WS_HANDSHAKE_ACCEPT_KEY_LEN);

    /*  Lookup SP header value. */
    for (i = 0; i < NN_WS_HANDSHAKE_SP_MAP_LEN; i++) {
        if (NN_WS_HANDSHAKE_SP_MAP [i].client ==
            self->pipebase->sock->socktype->protocol) {
            break;
        }
    }

    /*  Guarantee that the socket type was found in the map. */
    nn_assert (i < NN_WS_HANDSHAKE_SP_MAP_LEN);

    sprintf (self->opening_hs,
        "GET %s HTTP/1.1\r\n"
        "Host: %s\r\n"
        "Upgrade: websocket\r\n"
        "Connection: Upgrade\r\n"
        "Sec-WebSocket-Key: %s\r\n"
        "Sec-WebSocket-Version: 13\r\n"
        "Sec-WebSocket-Protocol: %s\r\n\r\n",
        self->resource, self->remote_host, encoded_key,
        NN_WS_HANDSHAKE_SP_MAP[i].ws_sp);

    open_request.iov_len = strlen (self->opening_hs);
    open_request.iov_base = self->opening_hs;

    nn_usock_send (self->usock, &open_request, 1);
}