#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct crypto_options {int dummy; } ;
struct context_buffers {int /*<<< orphan*/  read_tun_buf; int /*<<< orphan*/  encrypt_buf; int /*<<< orphan*/  compress_buf; } ;
struct TYPE_20__ {scalar_t__ len; int /*<<< orphan*/ * data; } ;
struct TYPE_18__ {scalar_t__ context_auth; TYPE_5__ buf; int /*<<< orphan*/  to_link; int /*<<< orphan*/  to_link_addr; TYPE_3__* tls_multi; struct crypto_options crypto_options; int /*<<< orphan*/  frame; int /*<<< orphan*/  frame_fragment; scalar_t__ fragment; TYPE_11__* comp_context; struct context_buffers* buffers; } ;
struct context {TYPE_2__ c2; } ;
struct TYPE_19__ {scalar_t__ use_peer_id; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* compress ) (TYPE_5__*,int /*<<< orphan*/ ,TYPE_11__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_16__ {TYPE_1__ alg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ CAS_SUCCEEDED ; 
 int /*<<< orphan*/  FRAME_HEADROOM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_turnover (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fragment_outgoing (scalar_t__,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_link_socket_info (struct context*) ; 
 int /*<<< orphan*/  link_socket_get_outgoing_addr (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  openvpn_encrypt (TYPE_5__*,int /*<<< orphan*/ ,struct crypto_options*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ ,TYPE_11__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_post_encrypt (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  tls_pre_encrypt (TYPE_3__*,TYPE_5__*,struct crypto_options**) ; 
 int /*<<< orphan*/  tls_prepend_opcode_v1 (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  tls_prepend_opcode_v2 (TYPE_3__*,int /*<<< orphan*/ *) ; 

void
encrypt_sign(struct context *c, bool comp_frag)
{
    struct context_buffers *b = c->c2.buffers;
    const uint8_t *orig_buf = c->c2.buf.data;
    struct crypto_options *co = NULL;

#if P2MP_SERVER
    /*
     * Drop non-TLS outgoing packet if client-connect script/plugin
     * has not yet succeeded.
     */
    if (c->c2.context_auth != CAS_SUCCEEDED)
    {
        c->c2.buf.len = 0;
    }
#endif

    if (comp_frag)
    {
#ifdef USE_COMP
        /* Compress the packet. */
        if (c->c2.comp_context)
        {
            (*c->c2.comp_context->alg.compress)(&c->c2.buf, b->compress_buf, c->c2.comp_context, &c->c2.frame);
        }
#endif
#ifdef ENABLE_FRAGMENT
        if (c->c2.fragment)
        {
            fragment_outgoing(c->c2.fragment, &c->c2.buf, &c->c2.frame_fragment);
        }
#endif
    }

    /* initialize work buffer with FRAME_HEADROOM bytes of prepend capacity */
    ASSERT(buf_init(&b->encrypt_buf, FRAME_HEADROOM(&c->c2.frame)));

    if (c->c2.tls_multi)
    {
        /* Get the key we will use to encrypt the packet. */
        tls_pre_encrypt(c->c2.tls_multi, &c->c2.buf, &co);
        /* If using P_DATA_V2, prepend the 1-byte opcode and 3-byte peer-id to the
         * packet before openvpn_encrypt(), so we can authenticate the opcode too.
         */
        if (c->c2.buf.len > 0 && c->c2.tls_multi->use_peer_id)
        {
            tls_prepend_opcode_v2(c->c2.tls_multi, &b->encrypt_buf);
        }
    }
    else
    {
        co = &c->c2.crypto_options;
    }

    /* Encrypt and authenticate the packet */
    openvpn_encrypt(&c->c2.buf, b->encrypt_buf, co);

    /* Do packet administration */
    if (c->c2.tls_multi)
    {
        if (c->c2.buf.len > 0 && !c->c2.tls_multi->use_peer_id)
        {
            tls_prepend_opcode_v1(c->c2.tls_multi, &c->c2.buf);
        }
        tls_post_encrypt(c->c2.tls_multi, &c->c2.buf);
    }

    /*
     * Get the address we will be sending the packet to.
     */
    link_socket_get_outgoing_addr(&c->c2.buf, get_link_socket_info(c),
                                  &c->c2.to_link_addr);

    /* if null encryption, copy result to read_tun_buf */
    buffer_turnover(orig_buf, &c->c2.to_link, &c->c2.buf, &b->read_tun_buf);
}