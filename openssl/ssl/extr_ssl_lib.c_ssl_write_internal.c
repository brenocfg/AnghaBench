#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int (* func_write ) (TYPE_3__*,void const*,size_t,size_t*) ;} ;
struct ssl_async_args {size_t num; TYPE_1__ f; int /*<<< orphan*/  type; void* buf; TYPE_3__* s; } ;
struct TYPE_10__ {int shutdown; scalar_t__ early_data_state; int mode; size_t asyncrw; TYPE_2__* method; int /*<<< orphan*/  rwstate; int /*<<< orphan*/ * handshake_func; } ;
struct TYPE_9__ {int (* ssl_write ) (TYPE_3__*,void const*,size_t,size_t*) ;} ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/ * ASYNC_get_current_job () ; 
 int /*<<< orphan*/  ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED ; 
 scalar_t__ SSL_EARLY_DATA_ACCEPT_RETRY ; 
 scalar_t__ SSL_EARLY_DATA_CONNECT_RETRY ; 
 scalar_t__ SSL_EARLY_DATA_READ_RETRY ; 
 int /*<<< orphan*/  SSL_F_SSL_WRITE_INTERNAL ; 
 int SSL_MODE_ASYNC ; 
 int /*<<< orphan*/  SSL_NOTHING ; 
 int /*<<< orphan*/  SSL_R_PROTOCOL_IS_SHUTDOWN ; 
 int /*<<< orphan*/  SSL_R_UNINITIALIZED ; 
 int SSL_SENT_SHUTDOWN ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITEFUNC ; 
 int /*<<< orphan*/  ossl_statem_check_finish_init (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ssl_io_intern ; 
 int ssl_start_async_job (TYPE_3__*,struct ssl_async_args*,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_3__*,void const*,size_t,size_t*) ; 

int ssl_write_internal(SSL *s, const void *buf, size_t num, size_t *written)
{
    if (s->handshake_func == NULL) {
        SSLerr(SSL_F_SSL_WRITE_INTERNAL, SSL_R_UNINITIALIZED);
        return -1;
    }

    if (s->shutdown & SSL_SENT_SHUTDOWN) {
        s->rwstate = SSL_NOTHING;
        SSLerr(SSL_F_SSL_WRITE_INTERNAL, SSL_R_PROTOCOL_IS_SHUTDOWN);
        return -1;
    }

    if (s->early_data_state == SSL_EARLY_DATA_CONNECT_RETRY
                || s->early_data_state == SSL_EARLY_DATA_ACCEPT_RETRY
                || s->early_data_state == SSL_EARLY_DATA_READ_RETRY) {
        SSLerr(SSL_F_SSL_WRITE_INTERNAL, ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED);
        return 0;
    }
    /* If we are a client and haven't sent the Finished we better do that */
    ossl_statem_check_finish_init(s, 1);

    if ((s->mode & SSL_MODE_ASYNC) && ASYNC_get_current_job() == NULL) {
        int ret;
        struct ssl_async_args args;

        args.s = s;
        args.buf = (void *)buf;
        args.num = num;
        args.type = WRITEFUNC;
        args.f.func_write = s->method->ssl_write;

        ret = ssl_start_async_job(s, &args, ssl_io_intern);
        *written = s->asyncrw;
        return ret;
    } else {
        return s->method->ssl_write(s, buf, num, written);
    }
}