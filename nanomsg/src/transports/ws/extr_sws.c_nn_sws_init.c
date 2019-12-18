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
struct TYPE_2__ {int src; int /*<<< orphan*/ * fsm; } ;
struct nn_sws {int instate; int outstate; int /*<<< orphan*/  done; scalar_t__ pongs_received; scalar_t__ pings_received; scalar_t__ pongs_sent; scalar_t__ pings_sent; scalar_t__ utf8_code_pt_fragment_len; int /*<<< orphan*/  utf8_code_pt_fragment; scalar_t__ continuing; int /*<<< orphan*/  outmsg; int /*<<< orphan*/  inmsg_array; int /*<<< orphan*/  pipebase; TYPE_1__ usock_owner; int /*<<< orphan*/ * usock; int /*<<< orphan*/  fsm; int /*<<< orphan*/  handshaker; int /*<<< orphan*/  state; } ;
struct nn_fsm {int dummy; } ;
struct nn_ep {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_SWS_SRC_HANDSHAKE ; 
 int /*<<< orphan*/  NN_SWS_STATE_IDLE ; 
 int /*<<< orphan*/  NN_SWS_UTF8_MAX_CODEPOINT_LEN ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_fsm_event_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_fsm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct nn_sws*,struct nn_fsm*) ; 
 int /*<<< orphan*/  nn_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_msg_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_pipebase_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nn_ep*) ; 
 int /*<<< orphan*/  nn_sws_handler ; 
 int /*<<< orphan*/  nn_sws_pipebase_vfptr ; 
 int /*<<< orphan*/  nn_sws_shutdown ; 
 int /*<<< orphan*/  nn_ws_handshake_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void nn_sws_init (struct nn_sws *self, int src,
    struct nn_ep *ep, struct nn_fsm *owner)
{
    nn_fsm_init (&self->fsm, nn_sws_handler, nn_sws_shutdown,
        src, self, owner);
    self->state = NN_SWS_STATE_IDLE;
    nn_ws_handshake_init (&self->handshaker,
        NN_SWS_SRC_HANDSHAKE, &self->fsm);
    self->usock = NULL;
    self->usock_owner.src = -1;
    self->usock_owner.fsm = NULL;
    nn_pipebase_init (&self->pipebase, &nn_sws_pipebase_vfptr, ep);
    self->instate = -1;
    nn_list_init (&self->inmsg_array);
    self->outstate = -1;
    nn_msg_init (&self->outmsg, 0);

    self->continuing = 0;

    memset (self->utf8_code_pt_fragment, 0,
        NN_SWS_UTF8_MAX_CODEPOINT_LEN);
    self->utf8_code_pt_fragment_len = 0;

    self->pings_sent = 0;
    self->pongs_sent = 0;
    self->pings_received = 0;
    self->pongs_received = 0;

    nn_fsm_event_init (&self->done);
}