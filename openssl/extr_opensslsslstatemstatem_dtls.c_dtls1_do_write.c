#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct hm_header_st {size_t msg_len; size_t frag_off; int /*<<< orphan*/  seq; int /*<<< orphan*/  type; } ;
struct TYPE_16__ {size_t init_off; size_t init_num; size_t max_send_fragment; scalar_t__ version; int /*<<< orphan*/  msg_callback_arg; TYPE_1__* init_buf; int /*<<< orphan*/  (* msg_callback ) (int,scalar_t__,int,int /*<<< orphan*/ *,size_t,TYPE_3__*,int /*<<< orphan*/ ) ;TYPE_2__* d1; int /*<<< orphan*/  rwstate; int /*<<< orphan*/  wbio; scalar_t__ enc_write_ctx; scalar_t__ write_hash; } ;
struct TYPE_15__ {size_t mtu; struct hm_header_st w_msg_hdr; int /*<<< orphan*/  retransmitting; } ;
struct TYPE_14__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_CTRL_DGRAM_MTU_EXCEEDED ; 
 scalar_t__ BIO_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int BIO_flush (int /*<<< orphan*/ ) ; 
 size_t BIO_wpending (int /*<<< orphan*/ ) ; 
 scalar_t__ DTLS1_BAD_VER ; 
 size_t DTLS1_HM_HEADER_LENGTH ; 
 size_t DTLS1_RT_HEADER_LENGTH ; 
 int EVP_CIPHER_CTX_block_size (scalar_t__) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_cipher (scalar_t__) ; 
 scalar_t__ EVP_CIPHER_CTX_mode (scalar_t__) ; 
 int EVP_CIPHER_flags (int /*<<< orphan*/ ) ; 
 scalar_t__ EVP_CIPH_CBC_MODE ; 
 int EVP_CIPH_FLAG_AEAD_CIPHER ; 
 size_t EVP_MD_CTX_size (scalar_t__) ; 
 int SSL3_RT_HANDSHAKE ; 
 int /*<<< orphan*/  SSL_NOTHING ; 
 int SSL_OP_NO_QUERY_MTU ; 
 int /*<<< orphan*/  SSL_WRITING ; 
 int SSL_get_options (TYPE_3__*) ; 
 int /*<<< orphan*/  SSL_get_wbio (TYPE_3__*) ; 
 int /*<<< orphan*/  dtls1_fix_message_header (TYPE_3__*,size_t,size_t) ; 
 size_t dtls1_min_mtu (TYPE_3__*) ; 
 int /*<<< orphan*/  dtls1_query_mtu (TYPE_3__*) ; 
 int dtls1_write_bytes (TYPE_3__*,int,int /*<<< orphan*/ *,size_t,size_t*) ; 
 int /*<<< orphan*/  dtls1_write_message_header (TYPE_3__*,unsigned char*) ; 
 int /*<<< orphan*/  l2n3 (size_t,unsigned char*) ; 
 int /*<<< orphan*/  ossl_assert (int) ; 
 int /*<<< orphan*/  s2n (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  ssl3_finish_mac (TYPE_3__*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stub1 (int,scalar_t__,int,int /*<<< orphan*/ *,size_t,TYPE_3__*,int /*<<< orphan*/ ) ; 

int dtls1_do_write(SSL *s, int type)
{
    int ret;
    size_t written;
    size_t curr_mtu;
    int retry = 1;
    size_t len, frag_off, mac_size, blocksize, used_len;

    if (!dtls1_query_mtu(s))
        return -1;

    if (s->d1->mtu < dtls1_min_mtu(s))
        /* should have something reasonable now */
        return -1;

    if (s->init_off == 0 && type == SSL3_RT_HANDSHAKE) {
        if (!ossl_assert(s->init_num ==
                         s->d1->w_msg_hdr.msg_len + DTLS1_HM_HEADER_LENGTH))
            return -1;
    }

    if (s->write_hash) {
        if (s->enc_write_ctx
            && (EVP_CIPHER_flags(EVP_CIPHER_CTX_cipher(s->enc_write_ctx)) &
                EVP_CIPH_FLAG_AEAD_CIPHER) != 0)
            mac_size = 0;
        else
            mac_size = EVP_MD_CTX_size(s->write_hash);
    } else
        mac_size = 0;

    if (s->enc_write_ctx &&
        (EVP_CIPHER_CTX_mode(s->enc_write_ctx) == EVP_CIPH_CBC_MODE))
        blocksize = 2 * EVP_CIPHER_CTX_block_size(s->enc_write_ctx);
    else
        blocksize = 0;

    frag_off = 0;
    s->rwstate = SSL_NOTHING;

    /* s->init_num shouldn't ever be < 0...but just in case */
    while (s->init_num > 0) {
        if (type == SSL3_RT_HANDSHAKE && s->init_off != 0) {
            /* We must be writing a fragment other than the first one */

            if (frag_off > 0) {
                /* This is the first attempt at writing out this fragment */

                if (s->init_off <= DTLS1_HM_HEADER_LENGTH) {
                    /*
                     * Each fragment that was already sent must at least have
                     * contained the message header plus one other byte.
                     * Therefore |init_off| must have progressed by at least
                     * |DTLS1_HM_HEADER_LENGTH + 1| bytes. If not something went
                     * wrong.
                     */
                    return -1;
                }

                /*
                 * Adjust |init_off| and |init_num| to allow room for a new
                 * message header for this fragment.
                 */
                s->init_off -= DTLS1_HM_HEADER_LENGTH;
                s->init_num += DTLS1_HM_HEADER_LENGTH;
            } else {
                /*
                 * We must have been called again after a retry so use the
                 * fragment offset from our last attempt. We do not need
                 * to adjust |init_off| and |init_num| as above, because
                 * that should already have been done before the retry.
                 */
                frag_off = s->d1->w_msg_hdr.frag_off;
            }
        }

        used_len = BIO_wpending(s->wbio) + DTLS1_RT_HEADER_LENGTH
            + mac_size + blocksize;
        if (s->d1->mtu > used_len)
            curr_mtu = s->d1->mtu - used_len;
        else
            curr_mtu = 0;

        if (curr_mtu <= DTLS1_HM_HEADER_LENGTH) {
            /*
             * grr.. we could get an error if MTU picked was wrong
             */
            ret = BIO_flush(s->wbio);
            if (ret <= 0) {
                s->rwstate = SSL_WRITING;
                return ret;
            }
            used_len = DTLS1_RT_HEADER_LENGTH + mac_size + blocksize;
            if (s->d1->mtu > used_len + DTLS1_HM_HEADER_LENGTH) {
                curr_mtu = s->d1->mtu - used_len;
            } else {
                /* Shouldn't happen */
                return -1;
            }
        }

        /*
         * We just checked that s->init_num > 0 so this cast should be safe
         */
        if (((unsigned int)s->init_num) > curr_mtu)
            len = curr_mtu;
        else
            len = s->init_num;

        if (len > s->max_send_fragment)
            len = s->max_send_fragment;

        /*
         * XDTLS: this function is too long.  split out the CCS part
         */
        if (type == SSL3_RT_HANDSHAKE) {
            if (len < DTLS1_HM_HEADER_LENGTH) {
                /*
                 * len is so small that we really can't do anything sensible
                 * so fail
                 */
                return -1;
            }
            dtls1_fix_message_header(s, frag_off, len - DTLS1_HM_HEADER_LENGTH);

            dtls1_write_message_header(s,
                                       (unsigned char *)&s->init_buf->
                                       data[s->init_off]);
        }

        ret = dtls1_write_bytes(s, type, &s->init_buf->data[s->init_off], len,
                                &written);
        if (ret < 0) {
            /*
             * might need to update MTU here, but we don't know which
             * previous packet caused the failure -- so can't really
             * retransmit anything.  continue as if everything is fine and
             * wait for an alert to handle the retransmit
             */
            if (retry && BIO_ctrl(SSL_get_wbio(s),
                                  BIO_CTRL_DGRAM_MTU_EXCEEDED, 0, NULL) > 0) {
                if (!(SSL_get_options(s) & SSL_OP_NO_QUERY_MTU)) {
                    if (!dtls1_query_mtu(s))
                        return -1;
                    /* Have one more go */
                    retry = 0;
                } else
                    return -1;
            } else {
                return -1;
            }
        } else {

            /*
             * bad if this assert fails, only part of the handshake message
             * got sent.  but why would this happen?
             */
            if (!ossl_assert(len == written))
                return -1;

            if (type == SSL3_RT_HANDSHAKE && !s->d1->retransmitting) {
                /*
                 * should not be done for 'Hello Request's, but in that case
                 * we'll ignore the result anyway
                 */
                unsigned char *p =
                    (unsigned char *)&s->init_buf->data[s->init_off];
                const struct hm_header_st *msg_hdr = &s->d1->w_msg_hdr;
                size_t xlen;

                if (frag_off == 0 && s->version != DTLS1_BAD_VER) {
                    /*
                     * reconstruct message header is if it is being sent in
                     * single fragment
                     */
                    *p++ = msg_hdr->type;
                    l2n3(msg_hdr->msg_len, p);
                    s2n(msg_hdr->seq, p);
                    l2n3(0, p);
                    l2n3(msg_hdr->msg_len, p);
                    p -= DTLS1_HM_HEADER_LENGTH;
                    xlen = written;
                } else {
                    p += DTLS1_HM_HEADER_LENGTH;
                    xlen = written - DTLS1_HM_HEADER_LENGTH;
                }

                if (!ssl3_finish_mac(s, p, xlen))
                    return -1;
            }

            if (written == s->init_num) {
                if (s->msg_callback)
                    s->msg_callback(1, s->version, type, s->init_buf->data,
                                    (size_t)(s->init_off + s->init_num), s,
                                    s->msg_callback_arg);

                s->init_off = 0; /* done writing this message */
                s->init_num = 0;

                return 1;
            }
            s->init_off += written;
            s->init_num -= written;
            written -= DTLS1_HM_HEADER_LENGTH;
            frag_off += written;

            /*
             * We save the fragment offset for the next fragment so we have it
             * available in case of an IO retry. We don't know the length of the
             * next fragment yet so just set that to 0 for now. It will be
             * updated again later.
             */
            dtls1_fix_message_header(s, frag_off, 0);
        }
    }
    return 0;
}