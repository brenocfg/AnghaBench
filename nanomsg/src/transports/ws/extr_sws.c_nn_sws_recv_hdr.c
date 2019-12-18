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
struct nn_sws {int /*<<< orphan*/  inhdr; int /*<<< orphan*/  usock; int /*<<< orphan*/  instate; int /*<<< orphan*/  inmsg_control; scalar_t__ inmsg_total_size; scalar_t__ inmsg_current_chunk_len; scalar_t__ inmsg_chunks; int /*<<< orphan*/ * inmsg_current_chunk_buf; int /*<<< orphan*/  inmsg_array; int /*<<< orphan*/  continuing; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_SWS_FRAME_MAX_HDR_LEN ; 
 int /*<<< orphan*/  NN_SWS_FRAME_SIZE_INITIAL ; 
 int /*<<< orphan*/  NN_SWS_INSTATE_RECV_HDR ; 
 int /*<<< orphan*/  NN_SWS_PAYLOAD_MAX_LENGTH ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_usock_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nn_sws_recv_hdr (struct nn_sws *self)
{
    if (!self->continuing) {
        nn_assert (nn_list_empty (&self->inmsg_array));

        self->inmsg_current_chunk_buf = NULL;
        self->inmsg_chunks = 0;
        self->inmsg_current_chunk_len = 0;
        self->inmsg_total_size = 0;
    }

    memset (self->inmsg_control, 0, NN_SWS_PAYLOAD_MAX_LENGTH);
    memset (self->inhdr, 0, NN_SWS_FRAME_MAX_HDR_LEN);
    self->instate = NN_SWS_INSTATE_RECV_HDR;
    nn_usock_recv (self->usock, self->inhdr, NN_SWS_FRAME_SIZE_INITIAL, NULL);

    return 0;
}