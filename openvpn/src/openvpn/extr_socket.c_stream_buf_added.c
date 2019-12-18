#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int len; } ;
struct stream_buf {int len; scalar_t__ port_share_state; int error; int maxlen; TYPE_1__ buf; TYPE_1__ residual; } ;
typedef  int /*<<< orphan*/  packet_size_type ;
typedef  int /*<<< orphan*/  net_size ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int BLEN (TYPE_1__*) ; 
 int /*<<< orphan*/  D_STREAM_DEBUG ; 
 int /*<<< orphan*/  D_STREAM_ERRORS ; 
 int /*<<< orphan*/  M_WARN ; 
 scalar_t__ PS_DISABLED ; 
 scalar_t__ PS_ENABLED ; 
 scalar_t__ PS_FOREIGN ; 
 int /*<<< orphan*/  buf_copy_excess (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  buf_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_read (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dmsg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  is_openvpn_protocol (TYPE_1__*) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,...) ; 
 int ntohps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stream_buf_reset (struct stream_buf*) ; 
 int /*<<< orphan*/  stream_buf_set_next (struct stream_buf*) ; 

__attribute__((used)) static bool
stream_buf_added(struct stream_buf *sb,
                 int length_added)
{
    dmsg(D_STREAM_DEBUG, "STREAM: ADD length_added=%d", length_added);
    if (length_added > 0)
    {
        sb->buf.len += length_added;
    }

    /* if length unknown, see if we can get the length prefix from
     * the head of the buffer */
    if (sb->len < 0 && sb->buf.len >= (int) sizeof(packet_size_type))
    {
        packet_size_type net_size;

#if PORT_SHARE
        if (sb->port_share_state == PS_ENABLED)
        {
            if (!is_openvpn_protocol(&sb->buf))
            {
                msg(D_STREAM_ERRORS, "Non-OpenVPN client protocol detected");
                sb->port_share_state = PS_FOREIGN;
                sb->error = true;
                return false;
            }
            else
            {
                sb->port_share_state = PS_DISABLED;
            }
        }
#endif

        ASSERT(buf_read(&sb->buf, &net_size, sizeof(net_size)));
        sb->len = ntohps(net_size);

        if (sb->len < 1 || sb->len > sb->maxlen)
        {
            msg(M_WARN, "WARNING: Bad encapsulated packet length from peer (%d), which must be > 0 and <= %d -- please ensure that --tun-mtu or --link-mtu is equal on both peers -- this condition could also indicate a possible active attack on the TCP link -- [Attempting restart...]", sb->len, sb->maxlen);
            stream_buf_reset(sb);
            sb->error = true;
            return false;
        }
    }

    /* is our incoming packet fully read? */
    if (sb->len > 0 && sb->buf.len >= sb->len)
    {
        /* save any residual data that's part of the next packet */
        ASSERT(buf_init(&sb->residual, 0));
        if (sb->buf.len > sb->len)
        {
            ASSERT(buf_copy_excess(&sb->residual, &sb->buf, sb->len));
        }
        dmsg(D_STREAM_DEBUG, "STREAM: ADD returned TRUE, buf_len=%d, residual_len=%d",
             BLEN(&sb->buf),
             BLEN(&sb->residual));
        return true;
    }
    else
    {
        dmsg(D_STREAM_DEBUG, "STREAM: ADD returned FALSE (have=%d need=%d)", sb->buf.len, sb->len);
        stream_buf_set_next(sb);
        return false;
    }
}