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
typedef  int /*<<< orphan*/  uint8_t ;
struct nn_sws {size_t inmsg_current_chunk_len; int utf8_code_pt_fragment_len; int /*<<< orphan*/  pipebase; int /*<<< orphan*/  instate; scalar_t__ is_final_frame; int /*<<< orphan*/ * utf8_code_pt_fragment; int /*<<< orphan*/ * inmsg_current_chunk_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_SWS_CLOSE_ERR_INVALID_FRAME ; 
 int /*<<< orphan*/  NN_SWS_INSTATE_RECVD_CHUNKED ; 
 int NN_SWS_UTF8_FRAGMENT ; 
 int NN_SWS_UTF8_INVALID ; 
 size_t NN_SWS_UTF8_MAX_CODEPOINT_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int /*<<< orphan*/  nn_pipebase_received (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_sws_fail_conn (struct nn_sws*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nn_sws_recv_hdr (struct nn_sws*) ; 
 int nn_utf8_code_point (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void nn_sws_validate_utf8_chunk (struct nn_sws *self)
{
    uint8_t *pos;
    int code_point_len;
    size_t len;

    len = self->inmsg_current_chunk_len;
    pos = self->inmsg_current_chunk_buf;

    /*  For chunked transfers, it's possible that a previous chunk was cut
        intra-code point. That partially-validated code point is reassembled
        with the beginning of the current chunk and checked. */
    if (self->utf8_code_pt_fragment_len) {

        nn_assert (self->utf8_code_pt_fragment_len <
            NN_SWS_UTF8_MAX_CODEPOINT_LEN);

        /*  Keep adding octets from fresh buffer to previous code point
            fragment to check for validity. */
        while (len > 0) {
            self->utf8_code_pt_fragment [self->utf8_code_pt_fragment_len] = *pos;
            self->utf8_code_pt_fragment_len++;
            pos++;
            len--;

            code_point_len = nn_utf8_code_point (self->utf8_code_pt_fragment,
                self->utf8_code_pt_fragment_len);

            if (code_point_len > 0) {
                /*  Valid code point found; continue validating. */
                break;
            }
            else if (code_point_len == NN_SWS_UTF8_INVALID) {
                nn_sws_fail_conn (self, NN_SWS_CLOSE_ERR_INVALID_FRAME,
                    "Invalid UTF-8 code point split on previous frame.");
                return;
            }
            else if (code_point_len == NN_SWS_UTF8_FRAGMENT) {
                if (self->is_final_frame) {
                    nn_sws_fail_conn (self, NN_SWS_CLOSE_ERR_INVALID_FRAME,
                        "Truncated UTF-8 payload with invalid code point.");
                    return;
                }
                else {
                    /*  This chunk is well-formed; now recv the next chunk. */
                    nn_sws_recv_hdr (self);
                    return;
                }
            }
        }
    }

    if (self->utf8_code_pt_fragment_len >= NN_SWS_UTF8_MAX_CODEPOINT_LEN)
        nn_assert (0);

    while (len > 0) {
        code_point_len = nn_utf8_code_point (pos, len);

        if (code_point_len > 0) {
            /*  Valid code point found; continue validating. */
            nn_assert (len >= (size_t) code_point_len);
            len -= code_point_len;
            pos += code_point_len;
            continue;
        }
        else if (code_point_len == NN_SWS_UTF8_INVALID) {
            self->utf8_code_pt_fragment_len = 0;
            memset (self->utf8_code_pt_fragment, 0,
                NN_SWS_UTF8_MAX_CODEPOINT_LEN);
            nn_sws_fail_conn (self, NN_SWS_CLOSE_ERR_INVALID_FRAME,
                "Invalid UTF-8 code point in payload.");
            return;
        }
        else if (code_point_len == NN_SWS_UTF8_FRAGMENT) {
            nn_assert (len < NN_SWS_UTF8_MAX_CODEPOINT_LEN);
            self->utf8_code_pt_fragment_len = len;
            memcpy (self->utf8_code_pt_fragment, pos, len);
            if (self->is_final_frame) {
                nn_sws_fail_conn (self, NN_SWS_CLOSE_ERR_INVALID_FRAME,
                    "Truncated UTF-8 payload with invalid code point.");
            }
            else {
                /*  Previous frame ended in the middle of a code point;
                    receive more. */
                nn_sws_recv_hdr (self);
            }
            return;
        }
    }

    /*  Entire buffer is well-formed. */
    nn_assert (len == 0);

    self->utf8_code_pt_fragment_len = 0;
    memset (self->utf8_code_pt_fragment, 0, NN_SWS_UTF8_MAX_CODEPOINT_LEN);

    if (self->is_final_frame) {
        self->instate = NN_SWS_INSTATE_RECVD_CHUNKED;
        nn_pipebase_received (&self->pipebase);
    }
    else {
        nn_sws_recv_hdr (self);
    }

    return;
}