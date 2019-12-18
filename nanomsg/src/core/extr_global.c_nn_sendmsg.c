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
struct nn_sock {int dummy; } ;
struct nn_msghdr {int msg_iovlen; unsigned char* msg_control; scalar_t__ msg_controllen; struct nn_iovec* msg_iov; } ;
struct nn_msg {int /*<<< orphan*/  body; int /*<<< orphan*/  sphdr; int /*<<< orphan*/  hdrs; } ;
struct nn_iovec {scalar_t__ iov_len; unsigned char* iov_base; } ;
struct nn_cmsghdr {scalar_t__ cmsg_level; scalar_t__ cmsg_type; size_t cmsg_len; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 unsigned char* NN_CMSG_DATA (struct nn_cmsghdr*) ; 
 struct nn_cmsghdr* NN_CMSG_FIRSTHDR (struct nn_msghdr const*) ; 
 struct nn_cmsghdr* NN_CMSG_NXTHDR (struct nn_msghdr const*,struct nn_cmsghdr*) ; 
 size_t NN_CMSG_SPACE (int /*<<< orphan*/ ) ; 
 scalar_t__ NN_MSG ; 
 int /*<<< orphan*/  NN_STAT_BYTES_SENT ; 
 int /*<<< orphan*/  NN_STAT_MESSAGES_SENT ; 
 scalar_t__ PROTO_SP ; 
 scalar_t__ SP_HDR ; 
 int errno ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 size_t nn_chunk_size (void*) ; 
 int /*<<< orphan*/ * nn_chunkref_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_chunkref_init (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  nn_chunkref_init_chunk (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  nn_chunkref_term (int /*<<< orphan*/ *) ; 
 int nn_global_hold_socket (struct nn_sock**,int) ; 
 int /*<<< orphan*/  nn_global_rele_socket (struct nn_sock*) ; 
 int /*<<< orphan*/  nn_msg_init (struct nn_msg*,size_t) ; 
 int /*<<< orphan*/  nn_msg_init_chunk (struct nn_msg*,void*) ; 
 int /*<<< orphan*/  nn_msg_term (struct nn_msg*) ; 
 scalar_t__ nn_slow (int) ; 
 int nn_sock_send (struct nn_sock*,struct nn_msg*,int) ; 
 int /*<<< orphan*/  nn_sock_stat_increment (struct nn_sock*,int /*<<< orphan*/ ,size_t) ; 

int nn_sendmsg (int s, const struct nn_msghdr *msghdr, int flags)
{
    int rc;
    size_t sz;
    size_t spsz;
    int i;
    struct nn_iovec *iov;
    struct nn_msg msg;
    void *chunk;
    int nnmsg;
    struct nn_cmsghdr *cmsg;
    struct nn_sock *sock;

    rc = nn_global_hold_socket (&sock, s);
    if (nn_slow (rc < 0)) {
        errno = -rc;
        return -1;
    }

    if (nn_slow (!msghdr)) {
        rc = -EINVAL;
        goto fail;
    }

    if (nn_slow (msghdr->msg_iovlen < 0)) {
        rc = -EMSGSIZE;
        goto fail;
    }

    if (msghdr->msg_iovlen == 1 && msghdr->msg_iov [0].iov_len == NN_MSG) {
        chunk = *(void**) msghdr->msg_iov [0].iov_base;
        if (nn_slow (chunk == NULL)) {
            rc = -EFAULT;
            goto fail;
        }
        sz = nn_chunk_size (chunk);
        nn_msg_init_chunk (&msg, chunk);
        nnmsg = 1;
    }
    else {

        /*  Compute the total size of the message. */
        sz = 0;
        for (i = 0; i != msghdr->msg_iovlen; ++i) {
            iov = &msghdr->msg_iov [i];
            if (nn_slow (iov->iov_len == NN_MSG)) {
               rc = -EINVAL;
               goto fail;
            }
            if (nn_slow (!iov->iov_base && iov->iov_len)) {
                rc = -EFAULT;
                goto fail;
            }
            if (nn_slow (sz + iov->iov_len < sz)) {
                rc = -EINVAL;
                goto fail;
            }
            sz += iov->iov_len;
        }

        /*  Create a message object from the supplied scatter array. */
        nn_msg_init (&msg, sz);
        sz = 0;
        for (i = 0; i != msghdr->msg_iovlen; ++i) {
            iov = &msghdr->msg_iov [i];
            memcpy (((uint8_t*) nn_chunkref_data (&msg.body)) + sz,
                iov->iov_base, iov->iov_len);
            sz += iov->iov_len;
        }

        nnmsg = 0;
    }

    /*  Add ancillary data to the message. */
    if (msghdr->msg_control) {

        /*  Copy all headers. */
        /*  TODO: SP_HDR should not be copied here! */
        if (msghdr->msg_controllen == NN_MSG) {
            chunk = *((void**) msghdr->msg_control);
            nn_chunkref_term (&msg.hdrs);
            nn_chunkref_init_chunk (&msg.hdrs, chunk);
        }
        else {
            nn_chunkref_term (&msg.hdrs);
            nn_chunkref_init (&msg.hdrs, msghdr->msg_controllen);
            memcpy (nn_chunkref_data (&msg.hdrs),
                msghdr->msg_control, msghdr->msg_controllen);
        }

        /* Search for SP_HDR property. */
        cmsg = NN_CMSG_FIRSTHDR (msghdr);
        while (cmsg) {
            if (cmsg->cmsg_level == PROTO_SP && cmsg->cmsg_type == SP_HDR) {
                unsigned char *ptr = NN_CMSG_DATA (cmsg);
                size_t clen = cmsg->cmsg_len - NN_CMSG_SPACE (0);
                if (clen > sizeof (size_t)) {
                    spsz = *(size_t *)(void *)ptr;
                    if (spsz <= (clen - sizeof (size_t))) {
                        /*  Copy body of SP_HDR property into 'sphdr'. */
                        nn_chunkref_term (&msg.sphdr);
                        nn_chunkref_init (&msg.sphdr, spsz);
                         memcpy (nn_chunkref_data (&msg.sphdr),
                             ptr + sizeof (size_t), spsz);
                    }
                }
                break;
            }
            cmsg = NN_CMSG_NXTHDR (msghdr, cmsg);
        }
    }

    /*  Send it further down the stack. */
    rc = nn_sock_send (sock, &msg, flags);
    if (nn_slow (rc < 0)) {

        /*  If we are dealing with user-supplied buffer, detach it from
            the message object. */
        if (nnmsg)
            nn_chunkref_init (&msg.body, 0);

        nn_msg_term (&msg);
        goto fail;
    }

    /*  Adjust the statistics. */
    nn_sock_stat_increment (sock, NN_STAT_MESSAGES_SENT, 1);
    nn_sock_stat_increment (sock, NN_STAT_BYTES_SENT, sz);

    nn_global_rele_socket (sock);

    return (int) sz;

fail:
    nn_global_rele_socket (sock);

    errno = -rc;
    return -1;
}