#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ d; int /*<<< orphan*/  rrec; scalar_t__ numrpipes; int /*<<< orphan*/  s; int /*<<< orphan*/  rbuf; int /*<<< orphan*/ * wpend_buf; scalar_t__ wpend_ret; scalar_t__ wpend_type; scalar_t__ wpend_tot; scalar_t__ handshake_fragment_len; int /*<<< orphan*/  handshake_fragment; scalar_t__ wnum; scalar_t__ packet_length; int /*<<< orphan*/ * packet; int /*<<< orphan*/  rstate; } ;
typedef  TYPE_1__ RECORD_LAYER ;

/* Variables and functions */
 int /*<<< orphan*/  DTLS_RECORD_LAYER_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  RECORD_LAYER_reset_read_sequence (TYPE_1__*) ; 
 int /*<<< orphan*/  RECORD_LAYER_reset_write_sequence (TYPE_1__*) ; 
 int /*<<< orphan*/  SSL3_BUFFER_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL3_RECORD_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_MAX_PIPELINES ; 
 int /*<<< orphan*/  SSL_ST_READ_HEADER ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ssl3_release_write_buffer (int /*<<< orphan*/ ) ; 

void RECORD_LAYER_clear(RECORD_LAYER *rl)
{
    rl->rstate = SSL_ST_READ_HEADER;

    /*
     * Do I need to clear read_ahead? As far as I can tell read_ahead did not
     * previously get reset by SSL_clear...so I'll keep it that way..but is
     * that right?
     */

    rl->packet = NULL;
    rl->packet_length = 0;
    rl->wnum = 0;
    memset(rl->handshake_fragment, 0, sizeof(rl->handshake_fragment));
    rl->handshake_fragment_len = 0;
    rl->wpend_tot = 0;
    rl->wpend_type = 0;
    rl->wpend_ret = 0;
    rl->wpend_buf = NULL;

    SSL3_BUFFER_clear(&rl->rbuf);
    ssl3_release_write_buffer(rl->s);
    rl->numrpipes = 0;
    SSL3_RECORD_clear(rl->rrec, SSL_MAX_PIPELINES);

    RECORD_LAYER_reset_read_sequence(rl);
    RECORD_LAYER_reset_write_sequence(rl);

    if (rl->d)
        DTLS_RECORD_LAYER_clear(rl);
}