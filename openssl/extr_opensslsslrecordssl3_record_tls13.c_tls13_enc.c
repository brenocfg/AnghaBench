#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  recheader ;
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_24__ {TYPE_7__* new_cipher; } ;
struct TYPE_25__ {TYPE_8__ tmp; } ;
struct TYPE_23__ {int algorithm_enc; } ;
struct TYPE_20__ {scalar_t__ max_early_data; } ;
struct TYPE_22__ {TYPE_5__* cipher; TYPE_4__ ext; } ;
struct TYPE_21__ {int algorithm_enc; } ;
struct TYPE_17__ {scalar_t__ max_early_data; } ;
struct TYPE_19__ {TYPE_2__* cipher; TYPE_1__ ext; } ;
struct TYPE_18__ {int algorithm_enc; } ;
struct TYPE_16__ {unsigned char* write_iv; unsigned char* read_iv; scalar_t__ early_data_state; TYPE_9__ s3; TYPE_6__* psksession; TYPE_3__* session; int /*<<< orphan*/  rlayer; int /*<<< orphan*/ * enc_read_ctx; int /*<<< orphan*/ * enc_write_ctx; } ;
struct TYPE_15__ {scalar_t__ type; unsigned char* data; unsigned char* input; size_t length; size_t rec_version; } ;
typedef  TYPE_10__ SSL3_RECORD ;
typedef  TYPE_11__ SSL ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 size_t EVP_CCM8_TLS_TAG_LEN ; 
 size_t EVP_CCM_TLS_TAG_LEN ; 
 size_t EVP_CHACHAPOLY_TLS_TAG_LEN ; 
 scalar_t__ EVP_CIPHER_CTX_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,unsigned char*) ; 
 size_t EVP_CIPHER_CTX_iv_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_CTRL_AEAD_GET_TAG ; 
 int /*<<< orphan*/  EVP_CTRL_AEAD_SET_TAG ; 
 scalar_t__ EVP_CipherFinal_ex (int /*<<< orphan*/ *,unsigned char*,int*) ; 
 scalar_t__ EVP_CipherInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int) ; 
 scalar_t__ EVP_CipherUpdate (int /*<<< orphan*/ *,unsigned char*,int*,unsigned char*,unsigned int) ; 
 size_t EVP_GCM_TLS_TAG_LEN ; 
 int EVP_MAX_IV_LENGTH ; 
 unsigned char* RECORD_LAYER_get_read_sequence (int /*<<< orphan*/ *) ; 
 unsigned char* RECORD_LAYER_get_write_sequence (int /*<<< orphan*/ *) ; 
 size_t SEQ_NUM_SIZE ; 
 scalar_t__ SSL3_RT_ALERT ; 
 int SSL3_RT_HEADER_LENGTH ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int SSL_AES128CCM8 ; 
 int SSL_AES256CCM8 ; 
 int SSL_AESCCM ; 
 int SSL_AESGCM ; 
 int SSL_CHACHA20 ; 
 scalar_t__ SSL_EARLY_DATA_WRITE_RETRY ; 
 scalar_t__ SSL_EARLY_DATA_WRITING ; 
 int /*<<< orphan*/  SSL_F_TLS13_ENC ; 
 int /*<<< orphan*/  SSLfatal (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_get_total_written (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  WPACKET_init_static_len (int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u16 (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u8 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  ossl_assert (int) ; 

int tls13_enc(SSL *s, SSL3_RECORD *recs, size_t n_recs, int sending)
{
    EVP_CIPHER_CTX *ctx;
    unsigned char iv[EVP_MAX_IV_LENGTH], recheader[SSL3_RT_HEADER_LENGTH];
    size_t ivlen, taglen, offset, loop, hdrlen;
    unsigned char *staticiv;
    unsigned char *seq;
    int lenu, lenf;
    SSL3_RECORD *rec = &recs[0];
    uint32_t alg_enc;
    WPACKET wpkt;

    if (n_recs != 1) {
        /* Should not happen */
        /* TODO(TLS1.3): Support pipelining */
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS13_ENC,
                 ERR_R_INTERNAL_ERROR);
        return -1;
    }

    if (sending) {
        ctx = s->enc_write_ctx;
        staticiv = s->write_iv;
        seq = RECORD_LAYER_get_write_sequence(&s->rlayer);
    } else {
        ctx = s->enc_read_ctx;
        staticiv = s->read_iv;
        seq = RECORD_LAYER_get_read_sequence(&s->rlayer);
    }

    /*
     * If we're sending an alert and ctx != NULL then we must be forcing
     * plaintext alerts. If we're reading and ctx != NULL then we allow
     * plaintext alerts at certain points in the handshake. If we've got this
     * far then we have already validated that a plaintext alert is ok here.
     */
    if (ctx == NULL || rec->type == SSL3_RT_ALERT) {
        memmove(rec->data, rec->input, rec->length);
        rec->input = rec->data;
        return 1;
    }

    ivlen = EVP_CIPHER_CTX_iv_length(ctx);

    if (s->early_data_state == SSL_EARLY_DATA_WRITING
            || s->early_data_state == SSL_EARLY_DATA_WRITE_RETRY) {
        if (s->session != NULL && s->session->ext.max_early_data > 0) {
            alg_enc = s->session->cipher->algorithm_enc;
        } else {
            if (!ossl_assert(s->psksession != NULL
                             && s->psksession->ext.max_early_data > 0)) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS13_ENC,
                         ERR_R_INTERNAL_ERROR);
                return -1;
            }
            alg_enc = s->psksession->cipher->algorithm_enc;
        }
    } else {
        /*
         * To get here we must have selected a ciphersuite - otherwise ctx would
         * be NULL
         */
        if (!ossl_assert(s->s3.tmp.new_cipher != NULL)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS13_ENC,
                     ERR_R_INTERNAL_ERROR);
            return -1;
        }
        alg_enc = s->s3.tmp.new_cipher->algorithm_enc;
    }

    if (alg_enc & SSL_AESCCM) {
        if (alg_enc & (SSL_AES128CCM8 | SSL_AES256CCM8))
            taglen = EVP_CCM8_TLS_TAG_LEN;
         else
            taglen = EVP_CCM_TLS_TAG_LEN;
         if (sending && EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_SET_TAG, taglen,
                                         NULL) <= 0) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS13_ENC,
                     ERR_R_INTERNAL_ERROR);
            return -1;
        }
    } else if (alg_enc & SSL_AESGCM) {
        taglen = EVP_GCM_TLS_TAG_LEN;
    } else if (alg_enc & SSL_CHACHA20) {
        taglen = EVP_CHACHAPOLY_TLS_TAG_LEN;
    } else {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS13_ENC,
                 ERR_R_INTERNAL_ERROR);
        return -1;
    }

    if (!sending) {
        /*
         * Take off tag. There must be at least one byte of content type as
         * well as the tag
         */
        if (rec->length < taglen + 1)
            return 0;
        rec->length -= taglen;
    }

    /* Set up IV */
    if (ivlen < SEQ_NUM_SIZE) {
        /* Should not happen */
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS13_ENC,
                 ERR_R_INTERNAL_ERROR);
        return -1;
    }
    offset = ivlen - SEQ_NUM_SIZE;
    memcpy(iv, staticiv, offset);
    for (loop = 0; loop < SEQ_NUM_SIZE; loop++)
        iv[offset + loop] = staticiv[offset + loop] ^ seq[loop];

    /* Increment the sequence counter */
    for (loop = SEQ_NUM_SIZE; loop > 0; loop--) {
        ++seq[loop - 1];
        if (seq[loop - 1] != 0)
            break;
    }
    if (loop == 0) {
        /* Sequence has wrapped */
        return -1;
    }

    /* TODO(size_t): lenu/lenf should be a size_t but EVP doesn't support it */
    if (EVP_CipherInit_ex(ctx, NULL, NULL, NULL, iv, sending) <= 0
            || (!sending && EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_SET_TAG,
                                             taglen,
                                             rec->data + rec->length) <= 0)) {
        return -1;
    }

    /* Set up the AAD */
    if (!WPACKET_init_static_len(&wpkt, recheader, sizeof(recheader), 0)
            || !WPACKET_put_bytes_u8(&wpkt, rec->type)
            || !WPACKET_put_bytes_u16(&wpkt, rec->rec_version)
            || !WPACKET_put_bytes_u16(&wpkt, rec->length + taglen)
            || !WPACKET_get_total_written(&wpkt, &hdrlen)
            || hdrlen != SSL3_RT_HEADER_LENGTH
            || !WPACKET_finish(&wpkt)) {
        WPACKET_cleanup(&wpkt);
        return -1;
    }

    /*
     * For CCM we must explicitly set the total plaintext length before we add
     * any AAD.
     */
    if (((alg_enc & SSL_AESCCM) != 0
                 && EVP_CipherUpdate(ctx, NULL, &lenu, NULL,
                                     (unsigned int)rec->length) <= 0)
            || EVP_CipherUpdate(ctx, NULL, &lenu, recheader,
                                sizeof(recheader)) <= 0
            || EVP_CipherUpdate(ctx, rec->data, &lenu, rec->input,
                                (unsigned int)rec->length) <= 0
            || EVP_CipherFinal_ex(ctx, rec->data + lenu, &lenf) <= 0
            || (size_t)(lenu + lenf) != rec->length) {
        return -1;
    }
    if (sending) {
        /* Add the tag */
        if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_GET_TAG, taglen,
                                rec->data + rec->length) <= 0) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS13_ENC,
                     ERR_R_INTERNAL_ERROR);
            return -1;
        }
        rec->length += taglen;
    }

    return 1;
}