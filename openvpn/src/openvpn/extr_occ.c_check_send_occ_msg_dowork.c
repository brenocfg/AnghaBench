#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int occ_op; int /*<<< orphan*/  buf; int /*<<< orphan*/  frame; int /*<<< orphan*/  occ_mtu_load_size; int /*<<< orphan*/  max_send_size_local; int /*<<< orphan*/  max_recv_size_local; int /*<<< orphan*/  options_string_local; TYPE_1__* buffers; } ;
struct context {TYPE_2__ c2; } ;
struct TYPE_3__ {int /*<<< orphan*/  aux_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BLEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  D_PACKET_CONTENT ; 
 int /*<<< orphan*/  EXPANDED_SIZE (int /*<<< orphan*/ *) ; 
 int EXTRA_FRAME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FRAME_HEADROOM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_RW_SIZE_TUN (int /*<<< orphan*/ *) ; 
#define  OCC_EXIT 134 
#define  OCC_MTU_LOAD 133 
#define  OCC_MTU_LOAD_REQUEST 132 
#define  OCC_MTU_REPLY 131 
#define  OCC_MTU_REQUEST 130 
#define  OCC_REPLY 129 
#define  OCC_REQUEST 128 
 scalar_t__ OCC_STRING_SIZE ; 
 int /*<<< orphan*/  buf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_safe (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  buf_write_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_write_u8 (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  dmsg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  encrypt_sign (struct context*,int) ; 
 int get_random () ; 
 scalar_t__ min_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  occ_magic ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void
check_send_occ_msg_dowork(struct context *c)
{
    bool doit = false;

    c->c2.buf = c->c2.buffers->aux_buf;
    ASSERT(buf_init(&c->c2.buf, FRAME_HEADROOM(&c->c2.frame)));
    ASSERT(buf_safe(&c->c2.buf, MAX_RW_SIZE_TUN(&c->c2.frame)));
    ASSERT(buf_write(&c->c2.buf, occ_magic, OCC_STRING_SIZE));

    switch (c->c2.occ_op)
    {
        case OCC_REQUEST:
            if (!buf_write_u8(&c->c2.buf, OCC_REQUEST))
            {
                break;
            }
            dmsg(D_PACKET_CONTENT, "SENT OCC_REQUEST");
            doit = true;
            break;

        case OCC_REPLY:
            if (!c->c2.options_string_local)
            {
                break;
            }
            if (!buf_write_u8(&c->c2.buf, OCC_REPLY))
            {
                break;
            }
            if (!buf_write(&c->c2.buf, c->c2.options_string_local,
                           strlen(c->c2.options_string_local) + 1))
            {
                break;
            }
            dmsg(D_PACKET_CONTENT, "SENT OCC_REPLY");
            doit = true;
            break;

        case OCC_MTU_REQUEST:
            if (!buf_write_u8(&c->c2.buf, OCC_MTU_REQUEST))
            {
                break;
            }
            dmsg(D_PACKET_CONTENT, "SENT OCC_MTU_REQUEST");
            doit = true;
            break;

        case OCC_MTU_REPLY:
            if (!buf_write_u8(&c->c2.buf, OCC_MTU_REPLY))
            {
                break;
            }
            if (!buf_write_u16(&c->c2.buf, c->c2.max_recv_size_local))
            {
                break;
            }
            if (!buf_write_u16(&c->c2.buf, c->c2.max_send_size_local))
            {
                break;
            }
            dmsg(D_PACKET_CONTENT, "SENT OCC_MTU_REPLY");
            doit = true;
            break;

        case OCC_MTU_LOAD_REQUEST:
            if (!buf_write_u8(&c->c2.buf, OCC_MTU_LOAD_REQUEST))
            {
                break;
            }
            if (!buf_write_u16(&c->c2.buf, c->c2.occ_mtu_load_size))
            {
                break;
            }
            dmsg(D_PACKET_CONTENT, "SENT OCC_MTU_LOAD_REQUEST");
            doit = true;
            break;

        case OCC_MTU_LOAD:
        {
            int need_to_add;

            if (!buf_write_u8(&c->c2.buf, OCC_MTU_LOAD))
            {
                break;
            }
            need_to_add = min_int(c->c2.occ_mtu_load_size, EXPANDED_SIZE(&c->c2.frame))
                          - OCC_STRING_SIZE
                          - sizeof(uint8_t)
                          - EXTRA_FRAME(&c->c2.frame);

            while (need_to_add > 0)
            {
                /*
                 * Fill the load test packet with pseudo-random bytes.
                 */
                if (!buf_write_u8(&c->c2.buf, get_random() & 0xFF))
                {
                    break;
                }
                --need_to_add;
            }
            dmsg(D_PACKET_CONTENT, "SENT OCC_MTU_LOAD min_int(%d-%d-%d-%d,%d) size=%d",
                 c->c2.occ_mtu_load_size,
                 OCC_STRING_SIZE,
                 (int) sizeof(uint8_t),
                 EXTRA_FRAME(&c->c2.frame),
                 MAX_RW_SIZE_TUN(&c->c2.frame),
                 BLEN(&c->c2.buf));
            doit = true;
        }
        break;

        case OCC_EXIT:
            if (!buf_write_u8(&c->c2.buf, OCC_EXIT))
            {
                break;
            }
            dmsg(D_PACKET_CONTENT, "SENT OCC_EXIT");
            doit = true;
            break;
    }

    if (doit)
    {
        /*
         * We will treat the packet like any other outgoing packet,
         * compress, encrypt, sign, etc.
         */
        encrypt_sign(c, true);
    }

    c->c2.occ_op = -1;
}