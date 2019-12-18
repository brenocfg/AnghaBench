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
struct nn_msghdr {int msg_iovlen; scalar_t__ msg_controllen; void* msg_control; struct nn_iovec* msg_iov; } ;
struct nn_msg {int /*<<< orphan*/  hdrs; int /*<<< orphan*/  sphdr; int /*<<< orphan*/  body; } ;
struct nn_iovec {scalar_t__ iov_len; char* iov_base; } ;
struct nn_cmsghdr {size_t cmsg_len; int /*<<< orphan*/  cmsg_type; int /*<<< orphan*/  cmsg_level; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 size_t NN_CMSG_SPACE (size_t) ; 
 scalar_t__ NN_MSG ; 
 int /*<<< orphan*/  NN_STAT_BYTES_RECEIVED ; 
 int /*<<< orphan*/  NN_STAT_MESSAGES_RECEIVED ; 
 int /*<<< orphan*/  PROTO_SP ; 
 int /*<<< orphan*/  SP_HDR ; 
 int errno ; 
 int /*<<< orphan*/  errnum_assert (int,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,size_t) ; 
 int nn_chunk_alloc (size_t,int /*<<< orphan*/ ,void**) ; 
 size_t nn_chunk_size (void*) ; 
 int /*<<< orphan*/ * nn_chunkref_data (int /*<<< orphan*/ *) ; 
 void* nn_chunkref_getchunk (int /*<<< orphan*/ *) ; 
 size_t nn_chunkref_size (int /*<<< orphan*/ *) ; 
 int nn_global_hold_socket (struct nn_sock**,int) ; 
 int /*<<< orphan*/  nn_global_rele_socket (struct nn_sock*) ; 
 int /*<<< orphan*/  nn_msg_term (struct nn_msg*) ; 
 scalar_t__ nn_slow (int) ; 
 int nn_sock_recv (struct nn_sock*,struct nn_msg*,int) ; 
 int /*<<< orphan*/  nn_sock_stat_increment (struct nn_sock*,int /*<<< orphan*/ ,size_t) ; 

int nn_recvmsg (int s, struct nn_msghdr *msghdr, int flags)
{
    int rc;
    struct nn_msg msg;
    uint8_t *data;
    size_t sz;
    int i;
    struct nn_iovec *iov;
    void *chunk;
    size_t hdrssz;
    void *ctrl;
    size_t ctrlsz;
    size_t spsz;
    size_t sptotalsz;
    struct nn_cmsghdr *chdr;
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

    /*  Get a message. */
    rc = nn_sock_recv (sock, &msg, flags);
    if (nn_slow (rc < 0)) {
        goto fail;
    }

    if (msghdr->msg_iovlen == 1 && msghdr->msg_iov [0].iov_len == NN_MSG) {
        chunk = nn_chunkref_getchunk (&msg.body);
        *(void**) (msghdr->msg_iov [0].iov_base) = chunk;
        sz = nn_chunk_size (chunk);
    }
    else {

        /*  Copy the message content into the supplied gather array. */
        data = nn_chunkref_data (&msg.body);
        sz = nn_chunkref_size (&msg.body);
        for (i = 0; i != msghdr->msg_iovlen; ++i) {
            iov = &msghdr->msg_iov [i];
            if (nn_slow (iov->iov_len == NN_MSG)) {
                nn_msg_term (&msg);
                rc = -EINVAL;
                goto fail;
            }
            if (iov->iov_len > sz) {
                memcpy (iov->iov_base, data, sz);
                break;
            }
            memcpy (iov->iov_base, data, iov->iov_len);
            data += iov->iov_len;
            sz -= iov->iov_len;
        }
        sz = nn_chunkref_size (&msg.body);
    }

    /*  Retrieve the ancillary data from the message. */
    if (msghdr->msg_control) {

        spsz = nn_chunkref_size (&msg.sphdr);
        sptotalsz = NN_CMSG_SPACE (spsz+sizeof (size_t));
        ctrlsz = sptotalsz + nn_chunkref_size (&msg.hdrs);

        if (msghdr->msg_controllen == NN_MSG) {

            /* Allocate the buffer. */
            rc = nn_chunk_alloc (ctrlsz, 0, &ctrl);
            errnum_assert (rc == 0, -rc);

            /* Set output parameters. */
            *((void**) msghdr->msg_control) = ctrl;
        }
        else {

            /* Just use the buffer supplied by the user. */
            ctrl = msghdr->msg_control;
            ctrlsz = msghdr->msg_controllen;
        }

        /* If SP header alone won't fit into the buffer, return no ancillary
           properties. */
        if (ctrlsz >= sptotalsz) {
            char *ptr;

            /*  Fill in SP_HDR ancillary property. */
            chdr = (struct nn_cmsghdr*) ctrl;
            chdr->cmsg_len = sptotalsz;
            chdr->cmsg_level = PROTO_SP;
            chdr->cmsg_type = SP_HDR;
            ptr = (void *)chdr;
            ptr += sizeof (*chdr);
            *(size_t *)(void *)ptr = spsz;
            ptr += sizeof (size_t);
            memcpy (ptr, nn_chunkref_data (&msg.sphdr), spsz);

            /*  Fill in as many remaining properties as possible.
                Truncate the trailing properties if necessary. */
            hdrssz = nn_chunkref_size (&msg.hdrs);
            if (hdrssz > ctrlsz - sptotalsz)
                hdrssz = ctrlsz - sptotalsz;
            memcpy (((char*) ctrl) + sptotalsz,
                nn_chunkref_data (&msg.hdrs), hdrssz);
        }
    }

    nn_msg_term (&msg);

    /*  Adjust the statistics. */
    nn_sock_stat_increment (sock, NN_STAT_MESSAGES_RECEIVED, 1);
    nn_sock_stat_increment (sock, NN_STAT_BYTES_RECEIVED, sz);

    nn_global_rele_socket (sock);

    return (int) sz;

fail:
    nn_global_rele_socket (sock);

    errno = -rc;
    return -1;
}