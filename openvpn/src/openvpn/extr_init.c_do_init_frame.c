#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  frame_fragment; int /*<<< orphan*/  frame_fragment_initial; int /*<<< orphan*/  frame_fragment_omit; int /*<<< orphan*/  frame; } ;
struct TYPE_4__ {scalar_t__ fragment; scalar_t__ mssfix; int /*<<< orphan*/  proto; int /*<<< orphan*/  tun_mtu_extra; scalar_t__ tun_mtu_extra_defined; scalar_t__ socks_proxy_server; } ;
struct TYPE_5__ {TYPE_1__ ce; scalar_t__ mtu_test; int /*<<< orphan*/  comp; } ;
struct context {TYPE_3__ c2; TYPE_2__ options; } ;

/* Variables and functions */
 scalar_t__ CIPHER_ENABLED (struct context*) ; 
 int /*<<< orphan*/  COMP_PREFIX_LEN ; 
 scalar_t__ ETHERNET_MTU ; 
 int FRAME_HEADROOM_MARKER_DECRYPT ; 
 int FRAME_HEADROOM_MARKER_FRAGMENT ; 
 int /*<<< orphan*/  M_WARN ; 
 scalar_t__ TUN_MTU_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  comp_add_to_extra_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  comp_add_to_extra_frame (int /*<<< orphan*/ *) ; 
 scalar_t__ comp_enabled (int /*<<< orphan*/ *) ; 
 scalar_t__ comp_unswapped_prefix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frame_add_to_align_adjust (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_add_to_extra_link (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  frame_finalize_options (struct context*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frame_or_align_flags (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  frame_subtract_extra (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  socket_adjust_frame_parameters (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socks_adjust_frame_parameters (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tun_adjust_frame_parameters (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_init_frame(struct context *c)
{
#ifdef USE_COMP
    /*
     * modify frame parameters if compression is enabled
     */
    if (comp_enabled(&c->options.comp))
    {
        comp_add_to_extra_frame(&c->c2.frame);

#if !defined(ENABLE_LZ4)
        /*
         * Compression usage affects buffer alignment when non-swapped algs
         * such as LZO is used.
         * Newer algs like LZ4 and comp-stub with COMP_F_SWAP don't need
         * any special alignment because of the control-byte swap approach.
         * LZO alignment (on the other hand) is problematic because
         * the presence of the control byte means that either the output of
         * decryption must be written to an unaligned buffer, or the input
         * to compression (or packet dispatch if packet is uncompressed)
         * must be read from an unaligned buffer.
         * This code tries to align the input to compression (or packet
         * dispatch if packet is uncompressed) at the cost of requiring
         * decryption output to be written to an unaligned buffer, so
         * it's more of a tradeoff than an optimal solution and we don't
         * include it when we are doing a modern build with LZ4.
         * Strictly speaking, on the server it would be better to execute
         * this code for every connection after we decide the compression
         * method, but currently the frame code doesn't appear to be
         * flexible enough for this, since the frame is already established
         * before it is known which compression options will be pushed.
         */
        if (comp_unswapped_prefix(&c->options.comp) && CIPHER_ENABLED(c))
        {
            frame_add_to_align_adjust(&c->c2.frame, COMP_PREFIX_LEN);
            frame_or_align_flags(&c->c2.frame,
                                 FRAME_HEADROOM_MARKER_FRAGMENT
                                 |FRAME_HEADROOM_MARKER_DECRYPT);
        }
#endif

#ifdef ENABLE_FRAGMENT
        comp_add_to_extra_frame(&c->c2.frame_fragment_omit); /* omit compression frame delta from final frame_fragment */
#endif
    }
#endif /* USE_COMP */

    /*
     * Adjust frame size for UDP Socks support.
     */
    if (c->options.ce.socks_proxy_server)
    {
        socks_adjust_frame_parameters(&c->c2.frame, c->options.ce.proto);
    }

    /*
     * Adjust frame size based on the --tun-mtu-extra parameter.
     */
    if (c->options.ce.tun_mtu_extra_defined)
    {
        tun_adjust_frame_parameters(&c->c2.frame, c->options.ce.tun_mtu_extra);
    }

    /*
     * Adjust frame size based on link socket parameters.
     * (Since TCP is a stream protocol, we need to insert
     * a packet length uint16_t in the buffer.)
     */
    socket_adjust_frame_parameters(&c->c2.frame, c->options.ce.proto);

    /*
     * Fill in the blanks in the frame parameters structure,
     * make sure values are rational, etc.
     */
    frame_finalize_options(c, NULL);

#ifdef USE_COMP
    /*
     * Modify frame parameters if compression is compiled in.
     * Should be called after frame_finalize_options.
     */
    comp_add_to_extra_buffer(&c->c2.frame);
#ifdef ENABLE_FRAGMENT
    comp_add_to_extra_buffer(&c->c2.frame_fragment_omit); /* omit compression frame delta from final frame_fragment */
#endif
#endif /* USE_COMP */

    /* packets with peer-id (P_DATA_V2) need 3 extra bytes in frame (on client)
     * and need link_mtu+3 bytes on socket reception (on server).
     *
     * accommodate receive path in f->extra_link, which has the side effect of
     * also increasing send buffers (BUF_SIZE() macro), which need to be
     * allocated big enough before receiving peer-id option from server.
     *
     * f->extra_frame is adjusted when peer-id option is push-received
     */
    frame_add_to_extra_link(&c->c2.frame, 3);

#ifdef ENABLE_FRAGMENT
    /*
     * Set frame parameter for fragment code.  This is necessary because
     * the fragmentation code deals with payloads which have already been
     * passed through the compression code.
     */
    c->c2.frame_fragment = c->c2.frame;
    frame_subtract_extra(&c->c2.frame_fragment, &c->c2.frame_fragment_omit);
    c->c2.frame_fragment_initial = c->c2.frame_fragment;
#endif

#if defined(ENABLE_FRAGMENT) && defined(ENABLE_OCC)
    /*
     * MTU advisories
     */
    if (c->options.ce.fragment && c->options.mtu_test)
    {
        msg(M_WARN,
            "WARNING: using --fragment and --mtu-test together may produce an inaccurate MTU test result");
    }
#endif

#ifdef ENABLE_FRAGMENT
    if ((c->options.ce.mssfix || c->options.ce.fragment)
        && TUN_MTU_SIZE(&c->c2.frame_fragment) != ETHERNET_MTU)
    {
        msg(M_WARN,
            "WARNING: normally if you use --mssfix and/or --fragment, you should also set --tun-mtu %d (currently it is %d)",
            ETHERNET_MTU, TUN_MTU_SIZE(&c->c2.frame_fragment));
    }
#endif
}