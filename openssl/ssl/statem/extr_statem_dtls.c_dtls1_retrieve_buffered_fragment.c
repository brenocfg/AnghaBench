#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ data; } ;
typedef  TYPE_3__ pitem ;
struct TYPE_12__ {scalar_t__ seq; size_t frag_len; size_t frag_off; } ;
struct TYPE_16__ {TYPE_10__ msg_header; int /*<<< orphan*/  fragment; int /*<<< orphan*/ * reassembly; } ;
typedef  TYPE_4__ hm_fragment ;
struct TYPE_17__ {scalar_t__ init_num; TYPE_2__* init_buf; TYPE_1__* d1; } ;
struct TYPE_14__ {scalar_t__ data; } ;
struct TYPE_13__ {scalar_t__ handshake_read_seq; int /*<<< orphan*/  buffered_messages; } ;
typedef  TYPE_5__ SSL ;

/* Variables and functions */
 int DTLS1_HM_HEADER_LENGTH ; 
 int /*<<< orphan*/  dtls1_hm_fragment_free (TYPE_4__*) ; 
 int dtls1_preprocess_fragment (TYPE_5__*,TYPE_10__*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  pitem_free (TYPE_3__*) ; 
 TYPE_3__* pqueue_peek (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pqueue_pop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dtls1_retrieve_buffered_fragment(SSL *s, size_t *len)
{
    /*-
     * (0) check whether the desired fragment is available
     * if so:
     * (1) copy over the fragment to s->init_buf->data[]
     * (2) update s->init_num
     */
    pitem *item;
    hm_fragment *frag;
    int ret;

    do {
        item = pqueue_peek(s->d1->buffered_messages);
        if (item == NULL)
            return 0;

        frag = (hm_fragment *)item->data;

        if (frag->msg_header.seq < s->d1->handshake_read_seq) {
            /* This is a stale message that has been buffered so clear it */
            pqueue_pop(s->d1->buffered_messages);
            dtls1_hm_fragment_free(frag);
            pitem_free(item);
            item = NULL;
            frag = NULL;
        }
    } while (item == NULL);

    /* Don't return if reassembly still in progress */
    if (frag->reassembly != NULL)
        return 0;

    if (s->d1->handshake_read_seq == frag->msg_header.seq) {
        size_t frag_len = frag->msg_header.frag_len;
        pqueue_pop(s->d1->buffered_messages);

        /* Calls SSLfatal() as required */
        ret = dtls1_preprocess_fragment(s, &frag->msg_header);

        if (ret && frag->msg_header.frag_len > 0) {
            unsigned char *p =
                (unsigned char *)s->init_buf->data + DTLS1_HM_HEADER_LENGTH;
            memcpy(&p[frag->msg_header.frag_off], frag->fragment,
                   frag->msg_header.frag_len);
        }

        dtls1_hm_fragment_free(frag);
        pitem_free(item);

        if (ret) {
            *len = frag_len;
            return 1;
        }

        /* Fatal error */
        s->init_num = 0;
        return -1;
    } else {
        return 0;
    }
}