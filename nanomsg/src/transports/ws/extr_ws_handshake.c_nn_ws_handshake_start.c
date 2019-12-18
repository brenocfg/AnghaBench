#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * fsm; int /*<<< orphan*/  src; } ;
struct nn_ws_handshake {int mode; char const* resource; char const* remote_host; int recv_len; int /*<<< orphan*/  fsm; scalar_t__ retries; scalar_t__ recv_pos; int /*<<< orphan*/  response; int /*<<< orphan*/  opening_hs; struct nn_pipebase* pipebase; struct nn_usock* usock; TYPE_1__ usock_owner; } ;
struct nn_usock {int dummy; } ;
struct nn_pipebase {int dummy; } ;

/* Variables and functions */
#define  NN_WS_CLIENT 129 
 int /*<<< orphan*/  NN_WS_HANDSHAKE_SRC_USOCK ; 
#define  NN_WS_SERVER 128 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int /*<<< orphan*/  nn_fsm_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_usock_swap_owner (struct nn_usock*,TYPE_1__*) ; 
 int strlen (char const*) ; 

void nn_ws_handshake_start (struct nn_ws_handshake *self,
    struct nn_usock *usock, struct nn_pipebase *pipebase,
    int mode, const char *resource, const char *host)
{
    /*  It's expected this resource has been allocated during intial connect. */
    if (mode == NN_WS_CLIENT)
        nn_assert (strlen (resource) >= 1);

    /*  Take ownership of the underlying socket. */
    nn_assert (self->usock == NULL && self->usock_owner.fsm == NULL);
    self->usock_owner.src = NN_WS_HANDSHAKE_SRC_USOCK;
    self->usock_owner.fsm = &self->fsm;
    nn_usock_swap_owner (usock, &self->usock_owner);
    self->usock = usock;
    self->pipebase = pipebase;
    self->mode = mode;
    self->resource = resource;
    self->remote_host = host;

    memset (self->opening_hs, 0, sizeof (self->opening_hs));
    memset (self->response, 0, sizeof (self->response));

    self->recv_pos = 0;
    self->retries = 0;

    /*  Calculate the absolute minimum length possible for a valid opening
        handshake. This is an optimization since we must poll for the
        remainder of the opening handshake in small byte chunks. */
    switch (self->mode) {
    case NN_WS_SERVER:
        self->recv_len = strlen (
            "GET x HTTP/1.1\r\n"
            "Upgrade: websocket\r\n"
            "Connection: Upgrade\r\n"
            "Host: x\r\n"
            "Origin: x\r\n"
            "Sec-WebSocket-Key: xxxxxxxxxxxxxxxxxxxxxxxx\r\n"
            "Sec-WebSocket-Version: xx\r\n\r\n");
        break;
    case NN_WS_CLIENT:
        /*  Shortest conceiveable response from server is a terse status. */
        self->recv_len = strlen ("HTTP/1.1 xxx\r\n\r\n");
        break;
    default:
        /*  Developer error; unexpected mode. */
        nn_assert (0);
        break;
    }

    /*  Launch the state machine. */
    nn_fsm_start (&self->fsm);
}