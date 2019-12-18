#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ warn_alert; } ;
struct TYPE_12__ {int shutdown; TYPE_1__ s3; int /*<<< orphan*/ * wbio; } ;
typedef  TYPE_2__ SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int BIO_RR_ACCEPT ; 
 int BIO_RR_CONNECT ; 
 int BIO_get_retry_reason (int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_should_io_special (int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_should_read (int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_should_write (int /*<<< orphan*/ *) ; 
 scalar_t__ ERR_GET_LIB (unsigned long) ; 
 scalar_t__ ERR_LIB_SYS ; 
 unsigned long ERR_peek_error () ; 
 scalar_t__ SSL_AD_CLOSE_NOTIFY ; 
 int SSL_ERROR_NONE ; 
 int SSL_ERROR_SSL ; 
 int SSL_ERROR_SYSCALL ; 
 int SSL_ERROR_WANT_ACCEPT ; 
 int SSL_ERROR_WANT_ASYNC ; 
 int SSL_ERROR_WANT_ASYNC_JOB ; 
 int SSL_ERROR_WANT_CLIENT_HELLO_CB ; 
 int SSL_ERROR_WANT_CONNECT ; 
 int SSL_ERROR_WANT_READ ; 
 int SSL_ERROR_WANT_WRITE ; 
 int SSL_ERROR_WANT_X509_LOOKUP ; 
 int SSL_ERROR_ZERO_RETURN ; 
 int SSL_RECEIVED_SHUTDOWN ; 
 int /*<<< orphan*/ * SSL_get_rbio (TYPE_2__ const*) ; 
 scalar_t__ SSL_want_async (TYPE_2__ const*) ; 
 scalar_t__ SSL_want_async_job (TYPE_2__ const*) ; 
 scalar_t__ SSL_want_client_hello_cb (TYPE_2__ const*) ; 
 scalar_t__ SSL_want_read (TYPE_2__ const*) ; 
 scalar_t__ SSL_want_write (TYPE_2__ const*) ; 
 scalar_t__ SSL_want_x509_lookup (TYPE_2__ const*) ; 

int SSL_get_error(const SSL *s, int i)
{
    int reason;
    unsigned long l;
    BIO *bio;

    if (i > 0)
        return SSL_ERROR_NONE;

    /*
     * Make things return SSL_ERROR_SYSCALL when doing SSL_do_handshake etc,
     * where we do encode the error
     */
    if ((l = ERR_peek_error()) != 0) {
        if (ERR_GET_LIB(l) == ERR_LIB_SYS)
            return SSL_ERROR_SYSCALL;
        else
            return SSL_ERROR_SSL;
    }

    if (SSL_want_read(s)) {
        bio = SSL_get_rbio(s);
        if (BIO_should_read(bio))
            return SSL_ERROR_WANT_READ;
        else if (BIO_should_write(bio))
            /*
             * This one doesn't make too much sense ... We never try to write
             * to the rbio, and an application program where rbio and wbio
             * are separate couldn't even know what it should wait for.
             * However if we ever set s->rwstate incorrectly (so that we have
             * SSL_want_read(s) instead of SSL_want_write(s)) and rbio and
             * wbio *are* the same, this test works around that bug; so it
             * might be safer to keep it.
             */
            return SSL_ERROR_WANT_WRITE;
        else if (BIO_should_io_special(bio)) {
            reason = BIO_get_retry_reason(bio);
            if (reason == BIO_RR_CONNECT)
                return SSL_ERROR_WANT_CONNECT;
            else if (reason == BIO_RR_ACCEPT)
                return SSL_ERROR_WANT_ACCEPT;
            else
                return SSL_ERROR_SYSCALL; /* unknown */
        }
    }

    if (SSL_want_write(s)) {
        /* Access wbio directly - in order to use the buffered bio if present */
        bio = s->wbio;
        if (BIO_should_write(bio))
            return SSL_ERROR_WANT_WRITE;
        else if (BIO_should_read(bio))
            /*
             * See above (SSL_want_read(s) with BIO_should_write(bio))
             */
            return SSL_ERROR_WANT_READ;
        else if (BIO_should_io_special(bio)) {
            reason = BIO_get_retry_reason(bio);
            if (reason == BIO_RR_CONNECT)
                return SSL_ERROR_WANT_CONNECT;
            else if (reason == BIO_RR_ACCEPT)
                return SSL_ERROR_WANT_ACCEPT;
            else
                return SSL_ERROR_SYSCALL;
        }
    }
    if (SSL_want_x509_lookup(s))
        return SSL_ERROR_WANT_X509_LOOKUP;
    if (SSL_want_async(s))
        return SSL_ERROR_WANT_ASYNC;
    if (SSL_want_async_job(s))
        return SSL_ERROR_WANT_ASYNC_JOB;
    if (SSL_want_client_hello_cb(s))
        return SSL_ERROR_WANT_CLIENT_HELLO_CB;

    if ((s->shutdown & SSL_RECEIVED_SHUTDOWN) &&
        (s->s3.warn_alert == SSL_AD_CLOSE_NOTIFY))
        return SSL_ERROR_ZERO_RETURN;

    return SSL_ERROR_SYSCALL;
}