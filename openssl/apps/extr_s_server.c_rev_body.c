#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  info; } ;
struct TYPE_3__ {TYPE_2__* user; int /*<<< orphan*/  login; int /*<<< orphan*/  vb; } ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_CLOSE ; 
 int /*<<< orphan*/  BIO_NOCLOSE ; 
 scalar_t__ BIO_RR_SSL_X509_LOOKUP ; 
 int BIO_do_handshake (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_f_buffer () ; 
 int /*<<< orphan*/  BIO_f_ebcdic_filter () ; 
 int /*<<< orphan*/  BIO_f_ssl () ; 
 int BIO_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_get_retry_reason (int /*<<< orphan*/ *) ; 
 int BIO_gets (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BIO_new_socket (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_printf (scalar_t__,char*,...) ; 
 int /*<<< orphan*/ * BIO_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_puts (scalar_t__,char*) ; 
 int /*<<< orphan*/  BIO_set_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_set_callback_arg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BIO_set_ssl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_set_write_buffer_size (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ BIO_should_io_special (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_should_retry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_write (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  BUF_reverse (unsigned char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ERR_print_errors (scalar_t__) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 void* SRP_VBASE_get1_by_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRP_user_pwd_free (TYPE_2__*) ; 
 int SSL_RECEIVED_SHUTDOWN ; 
 int SSL_SENT_SHUTDOWN ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_get_rbio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_accept_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_msg_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_msg_callback_arg (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  SSL_set_session_id_context (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_shutdown (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_set_tlsext_debug_arg (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  SSL_set_tlsext_debug_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_trace ; 
 char* app_malloc (scalar_t__,char*) ; 
 int /*<<< orphan*/  bio_dump_callback ; 
 scalar_t__ bio_err ; 
 scalar_t__ bio_s_msg ; 
 scalar_t__ bio_s_out ; 
 scalar_t__ bufsize ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  msg_cb ; 
 int /*<<< orphan*/  print_ssl_summary (int /*<<< orphan*/ *) ; 
 scalar_t__ s_debug ; 
 int /*<<< orphan*/  s_ign_eof ; 
 int s_msg ; 
 int /*<<< orphan*/  s_quiet ; 
 scalar_t__ s_tlsextdebug ; 
 int /*<<< orphan*/  sleep (int) ; 
 TYPE_1__ srp_callback_parm ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  tlsext_cb ; 

__attribute__((used)) static int rev_body(int s, int stype, int prot, unsigned char *context)
{
    char *buf = NULL;
    int i;
    int ret = 1;
    SSL *con;
    BIO *io, *ssl_bio, *sbio;

    buf = app_malloc(bufsize, "server rev buffer");
    io = BIO_new(BIO_f_buffer());
    ssl_bio = BIO_new(BIO_f_ssl());
    if ((io == NULL) || (ssl_bio == NULL))
        goto err;

    /* lets make the output buffer a reasonable size */
    if (!BIO_set_write_buffer_size(io, bufsize))
        goto err;

    if ((con = SSL_new(ctx)) == NULL)
        goto err;

    if (s_tlsextdebug) {
        SSL_set_tlsext_debug_callback(con, tlsext_cb);
        SSL_set_tlsext_debug_arg(con, bio_s_out);
    }
    if (context != NULL
        && !SSL_set_session_id_context(con, context,
                                       strlen((char *)context))) {
        SSL_free(con);
        ERR_print_errors(bio_err);
        goto err;
    }

    sbio = BIO_new_socket(s, BIO_NOCLOSE);
    SSL_set_bio(con, sbio, sbio);
    SSL_set_accept_state(con);

    /* No need to free |con| after this. Done by BIO_free(ssl_bio) */
    BIO_set_ssl(ssl_bio, con, BIO_CLOSE);
    BIO_push(io, ssl_bio);
#ifdef CHARSET_EBCDIC
    io = BIO_push(BIO_new(BIO_f_ebcdic_filter()), io);
#endif

    if (s_debug) {
        BIO_set_callback(SSL_get_rbio(con), bio_dump_callback);
        BIO_set_callback_arg(SSL_get_rbio(con), (char *)bio_s_out);
    }
    if (s_msg) {
#ifndef OPENSSL_NO_SSL_TRACE
        if (s_msg == 2)
            SSL_set_msg_callback(con, SSL_trace);
        else
#endif
            SSL_set_msg_callback(con, msg_cb);
        SSL_set_msg_callback_arg(con, bio_s_msg ? bio_s_msg : bio_s_out);
    }

    for (;;) {
        i = BIO_do_handshake(io);
        if (i > 0)
            break;
        if (!BIO_should_retry(io)) {
            BIO_puts(bio_err, "CONNECTION FAILURE\n");
            ERR_print_errors(bio_err);
            goto end;
        }
#ifndef OPENSSL_NO_SRP
        if (BIO_should_io_special(io)
            && BIO_get_retry_reason(io) == BIO_RR_SSL_X509_LOOKUP) {
            BIO_printf(bio_s_out, "LOOKUP renego during accept\n");
            SRP_user_pwd_free(srp_callback_parm.user);
            srp_callback_parm.user =
                SRP_VBASE_get1_by_user(srp_callback_parm.vb,
                                       srp_callback_parm.login);
            if (srp_callback_parm.user)
                BIO_printf(bio_s_out, "LOOKUP done %s\n",
                           srp_callback_parm.user->info);
            else
                BIO_printf(bio_s_out, "LOOKUP not successful\n");
            continue;
        }
#endif
    }
    BIO_printf(bio_err, "CONNECTION ESTABLISHED\n");
    print_ssl_summary(con);

    for (;;) {
        i = BIO_gets(io, buf, bufsize - 1);
        if (i < 0) {            /* error */
            if (!BIO_should_retry(io)) {
                if (!s_quiet)
                    ERR_print_errors(bio_err);
                goto err;
            } else {
                BIO_printf(bio_s_out, "read R BLOCK\n");
#ifndef OPENSSL_NO_SRP
                if (BIO_should_io_special(io)
                    && BIO_get_retry_reason(io) == BIO_RR_SSL_X509_LOOKUP) {
                    BIO_printf(bio_s_out, "LOOKUP renego during read\n");
                    SRP_user_pwd_free(srp_callback_parm.user);
                    srp_callback_parm.user =
                        SRP_VBASE_get1_by_user(srp_callback_parm.vb,
                                               srp_callback_parm.login);
                    if (srp_callback_parm.user)
                        BIO_printf(bio_s_out, "LOOKUP done %s\n",
                                   srp_callback_parm.user->info);
                    else
                        BIO_printf(bio_s_out, "LOOKUP not successful\n");
                    continue;
                }
#endif
#if !defined(OPENSSL_SYS_MSDOS)
                sleep(1);
#endif
                continue;
            }
        } else if (i == 0) {    /* end of input */
            ret = 1;
            BIO_printf(bio_err, "CONNECTION CLOSED\n");
            goto end;
        } else {
            char *p = buf + i - 1;
            while (i && (*p == '\n' || *p == '\r')) {
                p--;
                i--;
            }
            if (!s_ign_eof && (i == 5) && (strncmp(buf, "CLOSE", 5) == 0)) {
                ret = 1;
                BIO_printf(bio_err, "CONNECTION CLOSED\n");
                goto end;
            }
            BUF_reverse((unsigned char *)buf, NULL, i);
            buf[i] = '\n';
            BIO_write(io, buf, i + 1);
            for (;;) {
                i = BIO_flush(io);
                if (i > 0)
                    break;
                if (!BIO_should_retry(io))
                    goto end;
            }
        }
    }
 end:
    /* make sure we re-use sessions */
    SSL_set_shutdown(con, SSL_SENT_SHUTDOWN | SSL_RECEIVED_SHUTDOWN);

 err:

    OPENSSL_free(buf);
    BIO_free_all(io);
    return ret;
}