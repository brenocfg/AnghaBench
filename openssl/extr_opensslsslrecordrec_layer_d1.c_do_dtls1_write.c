#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_39__   TYPE_7__ ;
typedef  struct TYPE_38__   TYPE_6__ ;
typedef  struct TYPE_37__   TYPE_5__ ;
typedef  struct TYPE_36__   TYPE_4__ ;
typedef  struct TYPE_35__   TYPE_3__ ;
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_1__ ;

/* Type definitions */
struct TYPE_37__ {size_t wpend_tot; unsigned char const* wpend_buf; int wpend_type; size_t wpend_ret; int /*<<< orphan*/ * write_sequence; TYPE_4__* d; int /*<<< orphan*/ * wbuf; } ;
struct TYPE_33__ {scalar_t__ alert_dispatch; } ;
struct TYPE_39__ {scalar_t__ max_proto_version; int version; TYPE_5__ rlayer; int /*<<< orphan*/  msg_callback_arg; int /*<<< orphan*/  (* msg_callback ) (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int,TYPE_7__*,int /*<<< orphan*/ ) ;TYPE_3__* method; int /*<<< orphan*/ * compress; int /*<<< orphan*/ * enc_write_ctx; int /*<<< orphan*/  write_hash; int /*<<< orphan*/ * session; TYPE_1__ s3; } ;
struct TYPE_38__ {size_t length; } ;
struct TYPE_36__ {size_t w_epoch; } ;
struct TYPE_35__ {int (* ssl_dispatch_alert ) (TYPE_7__*) ;scalar_t__ version; TYPE_2__* ssl3_enc; } ;
struct TYPE_34__ {int (* enc ) (TYPE_7__*,TYPE_6__*,int,int) ;int /*<<< orphan*/  (* mac ) (TYPE_7__*,TYPE_6__*,unsigned char*,int) ;} ;
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  TYPE_6__ SSL3_RECORD ;
typedef  int /*<<< orphan*/  SSL3_BUFFER ;
typedef  TYPE_7__ SSL ;

/* Variables and functions */
 scalar_t__ DTLS1_BAD_VER ; 
 int DTLS1_RT_HEADER_LENGTH ; 
 int DTLS1_VERSION ; 
 scalar_t__ DTLS_ANY_VERSION ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int EVP_CCM_TLS_EXPLICIT_IV_LEN ; 
 int EVP_CIPHER_CTX_iv_length (int /*<<< orphan*/ *) ; 
 int EVP_CIPHER_CTX_mode (int /*<<< orphan*/ *) ; 
 int EVP_CIPH_CBC_MODE ; 
 int EVP_CIPH_CCM_MODE ; 
 int EVP_CIPH_GCM_MODE ; 
 int EVP_GCM_TLS_EXPLICIT_IV_LEN ; 
 int /*<<< orphan*/ * EVP_MD_CTX_md (int /*<<< orphan*/ ) ; 
 int EVP_MD_CTX_size (int /*<<< orphan*/ ) ; 
 unsigned char* SSL3_BUFFER_get_buf (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL3_BUFFER_get_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL3_BUFFER_set_left (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  SSL3_BUFFER_set_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL3_RECORD_add_length (TYPE_6__*,int) ; 
 unsigned char* SSL3_RECORD_get_data (TYPE_6__*) ; 
 int /*<<< orphan*/ * SSL3_RECORD_get_input (TYPE_6__*) ; 
 size_t SSL3_RECORD_get_length (TYPE_6__*) ; 
 int /*<<< orphan*/  SSL3_RECORD_reset_input (TYPE_6__*) ; 
 int /*<<< orphan*/  SSL3_RECORD_set_data (TYPE_6__*,unsigned char*) ; 
 int /*<<< orphan*/  SSL3_RECORD_set_input (TYPE_6__*,unsigned char*) ; 
 int /*<<< orphan*/  SSL3_RECORD_set_length (TYPE_6__*,size_t) ; 
 int /*<<< orphan*/  SSL3_RECORD_set_type (TYPE_6__*,int) ; 
 int /*<<< orphan*/  SSL3_RT_HEADER ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_DO_DTLS1_WRITE ; 
 int /*<<< orphan*/  SSL_R_COMPRESSION_FAILURE ; 
 int /*<<< orphan*/  SSL_R_EXCEEDS_MAX_FRAGMENT_SIZE ; 
 scalar_t__ SSL_WRITE_ETM (TYPE_7__*) ; 
 int /*<<< orphan*/  SSLfatal (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ossl_assert (int) ; 
 int /*<<< orphan*/  ossl_statem_in_error (TYPE_7__*) ; 
 int /*<<< orphan*/  s2n (size_t,unsigned char*) ; 
 int /*<<< orphan*/  ssl3_do_compress (TYPE_7__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ssl3_record_sequence_update (int /*<<< orphan*/ *) ; 
 int ssl3_write_pending (TYPE_7__*,int,unsigned char const*,size_t,size_t*) ; 
 size_t ssl_get_max_send_fragment (TYPE_7__*) ; 
 int stub1 (TYPE_7__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_7__*,TYPE_6__*,unsigned char*,int) ; 
 int stub3 (TYPE_7__*,TYPE_6__*,int,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_7__*,TYPE_6__*,unsigned char*,int) ; 
 int /*<<< orphan*/  stub5 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int,TYPE_7__*,int /*<<< orphan*/ ) ; 

int do_dtls1_write(SSL *s, int type, const unsigned char *buf,
                   size_t len, int create_empty_fragment, size_t *written)
{
    unsigned char *p, *pseq;
    int i, mac_size, clear = 0;
    size_t prefix_len = 0;
    int eivlen;
    SSL3_RECORD wr;
    SSL3_BUFFER *wb;
    SSL_SESSION *sess;

    wb = &s->rlayer.wbuf[0];

    /*
     * first check if there is a SSL3_BUFFER still being written out.  This
     * will happen with non blocking IO
     */
    if (!ossl_assert(SSL3_BUFFER_get_left(wb) == 0)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DO_DTLS1_WRITE,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }

    /* If we have an alert to send, lets send it */
    if (s->s3.alert_dispatch) {
        i = s->method->ssl_dispatch_alert(s);
        if (i <= 0)
            return i;
        /* if it went, fall through and send more stuff */
    }

    if (len == 0 && !create_empty_fragment)
        return 0;

    if (len > ssl_get_max_send_fragment(s)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DO_DTLS1_WRITE,
                 SSL_R_EXCEEDS_MAX_FRAGMENT_SIZE);
        return 0;
    }

    sess = s->session;

    if ((sess == NULL) ||
        (s->enc_write_ctx == NULL) || (EVP_MD_CTX_md(s->write_hash) == NULL))
        clear = 1;

    if (clear)
        mac_size = 0;
    else {
        mac_size = EVP_MD_CTX_size(s->write_hash);
        if (mac_size < 0) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DO_DTLS1_WRITE,
                     SSL_R_EXCEEDS_MAX_FRAGMENT_SIZE);
            return -1;
        }
    }

    p = SSL3_BUFFER_get_buf(wb) + prefix_len;

    /* write the header */

    *(p++) = type & 0xff;
    SSL3_RECORD_set_type(&wr, type);
    /*
     * Special case: for hello verify request, client version 1.0 and we
     * haven't decided which version to use yet send back using version 1.0
     * header: otherwise some clients will ignore it.
     */
    if (s->method->version == DTLS_ANY_VERSION &&
        s->max_proto_version != DTLS1_BAD_VER) {
        *(p++) = DTLS1_VERSION >> 8;
        *(p++) = DTLS1_VERSION & 0xff;
    } else {
        *(p++) = s->version >> 8;
        *(p++) = s->version & 0xff;
    }

    /* field where we are to write out packet epoch, seq num and len */
    pseq = p;
    p += 10;

    /* Explicit IV length, block ciphers appropriate version flag */
    if (s->enc_write_ctx) {
        int mode = EVP_CIPHER_CTX_mode(s->enc_write_ctx);
        if (mode == EVP_CIPH_CBC_MODE) {
            eivlen = EVP_CIPHER_CTX_iv_length(s->enc_write_ctx);
            if (eivlen <= 1)
                eivlen = 0;
        }
        /* Need explicit part of IV for GCM mode */
        else if (mode == EVP_CIPH_GCM_MODE)
            eivlen = EVP_GCM_TLS_EXPLICIT_IV_LEN;
        else if (mode == EVP_CIPH_CCM_MODE)
            eivlen = EVP_CCM_TLS_EXPLICIT_IV_LEN;
        else
            eivlen = 0;
    } else
        eivlen = 0;

    /* lets setup the record stuff. */
    SSL3_RECORD_set_data(&wr, p + eivlen); /* make room for IV in case of CBC */
    SSL3_RECORD_set_length(&wr, len);
    SSL3_RECORD_set_input(&wr, (unsigned char *)buf);

    /*
     * we now 'read' from wr.input, wr.length bytes into wr.data
     */

    /* first we compress */
    if (s->compress != NULL) {
        if (!ssl3_do_compress(s, &wr)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DO_DTLS1_WRITE,
                     SSL_R_COMPRESSION_FAILURE);
            return -1;
        }
    } else {
        memcpy(SSL3_RECORD_get_data(&wr), SSL3_RECORD_get_input(&wr),
               SSL3_RECORD_get_length(&wr));
        SSL3_RECORD_reset_input(&wr);
    }

    /*
     * we should still have the output to wr.data and the input from
     * wr.input.  Length should be wr.length. wr.data still points in the
     * wb->buf
     */

    if (!SSL_WRITE_ETM(s) && mac_size != 0) {
        if (!s->method->ssl3_enc->mac(s, &wr,
                                      &(p[SSL3_RECORD_get_length(&wr) + eivlen]),
                                      1)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DO_DTLS1_WRITE,
                     ERR_R_INTERNAL_ERROR);
            return -1;
        }
        SSL3_RECORD_add_length(&wr, mac_size);
    }

    /* this is true regardless of mac size */
    SSL3_RECORD_set_data(&wr, p);
    SSL3_RECORD_reset_input(&wr);

    if (eivlen)
        SSL3_RECORD_add_length(&wr, eivlen);

    if (s->method->ssl3_enc->enc(s, &wr, 1, 1) < 1) {
        if (!ossl_statem_in_error(s)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DO_DTLS1_WRITE,
                     ERR_R_INTERNAL_ERROR);
        }
        return -1;
    }

    if (SSL_WRITE_ETM(s) && mac_size != 0) {
        if (!s->method->ssl3_enc->mac(s, &wr,
                                      &(p[SSL3_RECORD_get_length(&wr)]), 1)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DO_DTLS1_WRITE,
                     ERR_R_INTERNAL_ERROR);
            return -1;
        }
        SSL3_RECORD_add_length(&wr, mac_size);
    }

    /* record length after mac and block padding */

    /* there's only one epoch between handshake and app data */

    s2n(s->rlayer.d->w_epoch, pseq);

    memcpy(pseq, &(s->rlayer.write_sequence[2]), 6);
    pseq += 6;
    s2n(SSL3_RECORD_get_length(&wr), pseq);

    if (s->msg_callback)
        s->msg_callback(1, 0, SSL3_RT_HEADER, pseq - DTLS1_RT_HEADER_LENGTH,
                        DTLS1_RT_HEADER_LENGTH, s, s->msg_callback_arg);

    /*
     * we should now have wr.data pointing to the encrypted data, which is
     * wr->length long
     */
    SSL3_RECORD_set_type(&wr, type); /* not needed but helps for debugging */
    SSL3_RECORD_add_length(&wr, DTLS1_RT_HEADER_LENGTH);

    ssl3_record_sequence_update(&(s->rlayer.write_sequence[0]));

    if (create_empty_fragment) {
        /*
         * we are in a recursive call; just return the length, don't write
         * out anything here
         */
        *written = wr.length;
        return 1;
    }

    /* now let's set up wb */
    SSL3_BUFFER_set_left(wb, prefix_len + SSL3_RECORD_get_length(&wr));
    SSL3_BUFFER_set_offset(wb, 0);

    /*
     * memorize arguments so that ssl3_write_pending can detect bad write
     * retries later
     */
    s->rlayer.wpend_tot = len;
    s->rlayer.wpend_buf = buf;
    s->rlayer.wpend_type = type;
    s->rlayer.wpend_ret = len;

    /* we now just need to write the buffer. Calls SSLfatal() as required. */
    return ssl3_write_pending(s, type, buf, len, written);
}