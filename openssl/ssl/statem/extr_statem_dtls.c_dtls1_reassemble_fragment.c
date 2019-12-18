#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_13__ ;

/* Type definitions */
struct hm_header_st {size_t frag_len; scalar_t__ frag_off; scalar_t__ msg_len; int seq; } ;
typedef  int /*<<< orphan*/  seq64be ;
struct TYPE_21__ {scalar_t__ data; } ;
typedef  TYPE_3__ pitem ;
struct TYPE_18__ {scalar_t__ frag_len; scalar_t__ msg_len; scalar_t__ frag_off; } ;
struct TYPE_22__ {unsigned char* fragment; int /*<<< orphan*/ * reassembly; TYPE_13__ msg_header; } ;
typedef  TYPE_4__ hm_fragment ;
typedef  int /*<<< orphan*/  devnull ;
struct TYPE_23__ {TYPE_2__* d1; TYPE_1__* method; } ;
struct TYPE_20__ {int /*<<< orphan*/  buffered_messages; } ;
struct TYPE_19__ {int (* ssl_read_bytes ) (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ ,size_t*) ;} ;
typedef  TYPE_5__ SSL ;

/* Variables and functions */
 int DTLS1_HM_FRAGMENT_RETRY ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSMBLY_BITMASK_IS_COMPLETE (int /*<<< orphan*/ *,long,int) ; 
 int /*<<< orphan*/  RSMBLY_BITMASK_MARK (int /*<<< orphan*/ *,long,long) ; 
 int /*<<< orphan*/  SSL3_RT_HANDSHAKE ; 
 int /*<<< orphan*/  dtls1_hm_fragment_free (TYPE_4__*) ; 
 TYPE_4__* dtls1_hm_fragment_new (scalar_t__,int) ; 
 scalar_t__ dtls1_max_handshake_message_len (TYPE_5__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_13__*,struct hm_header_st const*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ossl_assert (int) ; 
 TYPE_3__* pitem_new (unsigned char*,TYPE_4__*) ; 
 TYPE_3__* pqueue_find (int /*<<< orphan*/ ,unsigned char*) ; 
 TYPE_3__* pqueue_insert (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int stub1 (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ ,size_t*) ; 
 int stub2 (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,size_t,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static int
dtls1_reassemble_fragment(SSL *s, const struct hm_header_st *msg_hdr)
{
    hm_fragment *frag = NULL;
    pitem *item = NULL;
    int i = -1, is_complete;
    unsigned char seq64be[8];
    size_t frag_len = msg_hdr->frag_len;
    size_t readbytes;

    if ((msg_hdr->frag_off + frag_len) > msg_hdr->msg_len ||
        msg_hdr->msg_len > dtls1_max_handshake_message_len(s))
        goto err;

    if (frag_len == 0) {
        return DTLS1_HM_FRAGMENT_RETRY;
    }

    /* Try to find item in queue */
    memset(seq64be, 0, sizeof(seq64be));
    seq64be[6] = (unsigned char)(msg_hdr->seq >> 8);
    seq64be[7] = (unsigned char)msg_hdr->seq;
    item = pqueue_find(s->d1->buffered_messages, seq64be);

    if (item == NULL) {
        frag = dtls1_hm_fragment_new(msg_hdr->msg_len, 1);
        if (frag == NULL)
            goto err;
        memcpy(&(frag->msg_header), msg_hdr, sizeof(*msg_hdr));
        frag->msg_header.frag_len = frag->msg_header.msg_len;
        frag->msg_header.frag_off = 0;
    } else {
        frag = (hm_fragment *)item->data;
        if (frag->msg_header.msg_len != msg_hdr->msg_len) {
            item = NULL;
            frag = NULL;
            goto err;
        }
    }

    /*
     * If message is already reassembled, this must be a retransmit and can
     * be dropped. In this case item != NULL and so frag does not need to be
     * freed.
     */
    if (frag->reassembly == NULL) {
        unsigned char devnull[256];

        while (frag_len) {
            i = s->method->ssl_read_bytes(s, SSL3_RT_HANDSHAKE, NULL,
                                          devnull,
                                          frag_len >
                                          sizeof(devnull) ? sizeof(devnull) :
                                          frag_len, 0, &readbytes);
            if (i <= 0)
                goto err;
            frag_len -= readbytes;
        }
        return DTLS1_HM_FRAGMENT_RETRY;
    }

    /* read the body of the fragment (header has already been read */
    i = s->method->ssl_read_bytes(s, SSL3_RT_HANDSHAKE, NULL,
                                  frag->fragment + msg_hdr->frag_off,
                                  frag_len, 0, &readbytes);
    if (i <= 0 || readbytes != frag_len)
        i = -1;
    if (i <= 0)
        goto err;

    RSMBLY_BITMASK_MARK(frag->reassembly, (long)msg_hdr->frag_off,
                        (long)(msg_hdr->frag_off + frag_len));

    if (!ossl_assert(msg_hdr->msg_len > 0))
        goto err;
    RSMBLY_BITMASK_IS_COMPLETE(frag->reassembly, (long)msg_hdr->msg_len,
                               is_complete);

    if (is_complete) {
        OPENSSL_free(frag->reassembly);
        frag->reassembly = NULL;
    }

    if (item == NULL) {
        item = pitem_new(seq64be, frag);
        if (item == NULL) {
            i = -1;
            goto err;
        }

        item = pqueue_insert(s->d1->buffered_messages, item);
        /*
         * pqueue_insert fails iff a duplicate item is inserted. However,
         * |item| cannot be a duplicate. If it were, |pqueue_find|, above,
         * would have returned it and control would never have reached this
         * branch.
         */
        if (!ossl_assert(item != NULL))
            goto err;
    }

    return DTLS1_HM_FRAGMENT_RETRY;

 err:
    if (item == NULL)
        dtls1_hm_fragment_free(frag);
    return -1;
}