#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t renegotiate_count; size_t byte_count; unsigned long renegotiate_timeout; unsigned long last_time; int /*<<< orphan*/  num_renegotiates; int /*<<< orphan*/ * ssl; } ;
typedef  int /*<<< orphan*/  SSL ;
typedef  TYPE_1__ BIO_SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int BIO_RR_CONNECT ; 
 int BIO_RR_SSL_X509_LOOKUP ; 
 int /*<<< orphan*/  BIO_clear_retry_flags (int /*<<< orphan*/ *) ; 
 TYPE_1__* BIO_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_retry_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_retry_reason (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BIO_set_retry_special (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_retry_write (int /*<<< orphan*/ *) ; 
#define  SSL_ERROR_NONE 134 
#define  SSL_ERROR_SSL 133 
#define  SSL_ERROR_SYSCALL 132 
#define  SSL_ERROR_WANT_CONNECT 131 
#define  SSL_ERROR_WANT_READ 130 
#define  SSL_ERROR_WANT_WRITE 129 
#define  SSL_ERROR_WANT_X509_LOOKUP 128 
 int SSL_get_error (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_renegotiate (int /*<<< orphan*/ *) ; 
 int ssl_write_internal (int /*<<< orphan*/ *,char const*,size_t,size_t*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ssl_write(BIO *b, const char *buf, size_t size, size_t *written)
{
    int ret, r = 0;
    int retry_reason = 0;
    SSL *ssl;
    BIO_SSL *bs;

    if (buf == NULL)
        return 0;
    bs = BIO_get_data(b);
    ssl = bs->ssl;

    BIO_clear_retry_flags(b);

    ret = ssl_write_internal(ssl, buf, size, written);

    switch (SSL_get_error(ssl, ret)) {
    case SSL_ERROR_NONE:
        if (bs->renegotiate_count > 0) {
            bs->byte_count += *written;
            if (bs->byte_count > bs->renegotiate_count) {
                bs->byte_count = 0;
                bs->num_renegotiates++;
                SSL_renegotiate(ssl);
                r = 1;
            }
        }
        if ((bs->renegotiate_timeout > 0) && (!r)) {
            unsigned long tm;

            tm = (unsigned long)time(NULL);
            if (tm > bs->last_time + bs->renegotiate_timeout) {
                bs->last_time = tm;
                bs->num_renegotiates++;
                SSL_renegotiate(ssl);
            }
        }
        break;
    case SSL_ERROR_WANT_WRITE:
        BIO_set_retry_write(b);
        break;
    case SSL_ERROR_WANT_READ:
        BIO_set_retry_read(b);
        break;
    case SSL_ERROR_WANT_X509_LOOKUP:
        BIO_set_retry_special(b);
        retry_reason = BIO_RR_SSL_X509_LOOKUP;
        break;
    case SSL_ERROR_WANT_CONNECT:
        BIO_set_retry_special(b);
        retry_reason = BIO_RR_CONNECT;
    case SSL_ERROR_SYSCALL:
    case SSL_ERROR_SSL:
    default:
        break;
    }

    BIO_set_retry_reason(b, retry_reason);

    return ret;
}