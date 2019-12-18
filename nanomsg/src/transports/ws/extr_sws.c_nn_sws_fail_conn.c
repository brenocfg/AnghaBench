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
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct nn_sws {char* fail_msg; size_t fail_msg_len; int mode; scalar_t__ outstate; int /*<<< orphan*/  done; int /*<<< orphan*/  fsm; int /*<<< orphan*/  state; int /*<<< orphan*/  usock; int /*<<< orphan*/  inmsg_array; int /*<<< orphan*/  pipebase; int /*<<< orphan*/  instate; } ;
struct nn_iovec {char* iov_base; size_t iov_len; } ;

/* Variables and functions */
 size_t NN_SWS_CLOSE_CODE_LEN ; 
 int NN_SWS_FRAME_BITMASK_FIN ; 
 char NN_SWS_FRAME_BITMASK_MASKED ; 
 char NN_SWS_FRAME_BITMASK_NOT_MASKED ; 
 size_t NN_SWS_FRAME_SIZE_INITIAL ; 
 int NN_SWS_FRAME_SIZE_MASK ; 
 int /*<<< orphan*/  NN_SWS_INSTATE_CLOSED ; 
 scalar_t__ NN_SWS_OUTSTATE_IDLE ; 
 scalar_t__ NN_SWS_OUTSTATE_SENDING ; 
 size_t NN_SWS_PAYLOAD_MAX_LENGTH ; 
 int /*<<< orphan*/  NN_SWS_RETURN_CLOSE_HANDSHAKE ; 
 int /*<<< orphan*/  NN_SWS_STATE_ACTIVE ; 
 int /*<<< orphan*/  NN_SWS_STATE_CLOSING_CONNECTION ; 
 int /*<<< orphan*/  NN_SWS_STATE_DONE ; 
#define  NN_WS_CLIENT 129 
 int NN_WS_OPCODE_CLOSE ; 
#define  NN_WS_SERVER 128 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int /*<<< orphan*/  nn_assert_state (struct nn_sws*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_fsm_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_msg_array_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_pipebase_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_puts (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_random_generate (char*,int) ; 
 int /*<<< orphan*/  nn_sws_mask_payload (char*,size_t,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_usock_send (int /*<<< orphan*/ ,struct nn_iovec*,int) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static void nn_sws_fail_conn (struct nn_sws *self, int code, char *reason)
{
    size_t reason_len;
    size_t payload_len;
    uint8_t rand_mask [NN_SWS_FRAME_SIZE_MASK];
    uint8_t *payload_pos;
    struct nn_iovec iov;

    nn_assert_state (self, NN_SWS_STATE_ACTIVE);

    /*  Stop user send/recv actions. */
    self->instate = NN_SWS_INSTATE_CLOSED;
    nn_pipebase_stop (&self->pipebase);

    /*  Destroy any remnant incoming message fragments. */
    nn_msg_array_term (&self->inmsg_array);

    reason_len = strlen (reason);

    payload_len = reason_len + NN_SWS_CLOSE_CODE_LEN;

    /*  Ensure text is short enough to also include code and framing. */
    nn_assert (payload_len <= NN_SWS_PAYLOAD_MAX_LENGTH);

    /*  RFC 6455 section 5.5.1. */
    self->fail_msg [0] = (char)(NN_SWS_FRAME_BITMASK_FIN | NN_WS_OPCODE_CLOSE);

    /*  Size of the payload, which is the status code plus the reason. */
    self->fail_msg [1] = (char)payload_len;

    self->fail_msg_len = NN_SWS_FRAME_SIZE_INITIAL;

    switch (self->mode) {
    case NN_WS_SERVER:
        self->fail_msg [1] |= NN_SWS_FRAME_BITMASK_NOT_MASKED;
        break;
    case NN_WS_CLIENT:
        self->fail_msg [1] |= NN_SWS_FRAME_BITMASK_MASKED;

        /*  Generate 32-bit mask as per RFC 6455 5.3. */
        nn_random_generate (rand_mask, NN_SWS_FRAME_SIZE_MASK);

        memcpy (&self->fail_msg [NN_SWS_FRAME_SIZE_INITIAL],
            rand_mask, NN_SWS_FRAME_SIZE_MASK);

        self->fail_msg_len += NN_SWS_FRAME_SIZE_MASK;
        break;
    default:
        /*  Developer error. */
        nn_assert (0);
    }

    payload_pos = (uint8_t*) (&self->fail_msg [self->fail_msg_len]);

    /*  Copy Status Code in network order (big-endian). */
    nn_puts (payload_pos, (uint16_t) code);
    self->fail_msg_len += NN_SWS_CLOSE_CODE_LEN;

    /*  Copy Close Reason immediately following the code. */
    memcpy (payload_pos + NN_SWS_CLOSE_CODE_LEN, reason, reason_len);
    self->fail_msg_len += reason_len;

    /*  If this is a client, apply mask. */
    if (self->mode == NN_WS_CLIENT) {
        nn_sws_mask_payload (payload_pos, payload_len,
            rand_mask, NN_SWS_FRAME_SIZE_MASK, NULL);
    }


    if (self->outstate == NN_SWS_OUTSTATE_IDLE) {
        iov.iov_base = self->fail_msg;
        iov.iov_len = self->fail_msg_len;
        nn_usock_send (self->usock, &iov, 1);
        self->outstate = NN_SWS_OUTSTATE_SENDING;
        self->state = NN_SWS_STATE_CLOSING_CONNECTION;
    } else {
        self->state = NN_SWS_STATE_DONE;
        nn_fsm_raise (&self->fsm, &self->done, NN_SWS_RETURN_CLOSE_HANDSHAKE);
    }

    return;
}