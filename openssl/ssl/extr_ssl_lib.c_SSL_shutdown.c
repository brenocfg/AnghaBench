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
struct TYPE_9__ {int (* func_other ) (TYPE_3__*) ;} ;
struct ssl_async_args {TYPE_2__ f; int /*<<< orphan*/  type; TYPE_3__* s; } ;
struct TYPE_10__ {int mode; TYPE_1__* method; int /*<<< orphan*/ * handshake_func; } ;
struct TYPE_8__ {int (* ssl_shutdown ) (TYPE_3__*) ;} ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/ * ASYNC_get_current_job () ; 
 int /*<<< orphan*/  OTHERFUNC ; 
 int /*<<< orphan*/  SSL_F_SSL_SHUTDOWN ; 
 int SSL_MODE_ASYNC ; 
 int /*<<< orphan*/  SSL_R_SHUTDOWN_WHILE_IN_INIT ; 
 int /*<<< orphan*/  SSL_R_UNINITIALIZED ; 
 int /*<<< orphan*/  SSL_in_init (TYPE_3__*) ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_io_intern ; 
 int ssl_start_async_job (TYPE_3__*,struct ssl_async_args*,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_3__*) ; 

int SSL_shutdown(SSL *s)
{
    /*
     * Note that this function behaves differently from what one might
     * expect.  Return values are 0 for no success (yet), 1 for success; but
     * calling it once is usually not enough, even if blocking I/O is used
     * (see ssl3_shutdown).
     */

    if (s->handshake_func == NULL) {
        SSLerr(SSL_F_SSL_SHUTDOWN, SSL_R_UNINITIALIZED);
        return -1;
    }

    if (!SSL_in_init(s)) {
        if ((s->mode & SSL_MODE_ASYNC) && ASYNC_get_current_job() == NULL) {
            struct ssl_async_args args;

            args.s = s;
            args.type = OTHERFUNC;
            args.f.func_other = s->method->ssl_shutdown;

            return ssl_start_async_job(s, &args, ssl_io_intern);
        } else {
            return s->method->ssl_shutdown(s);
        }
    } else {
        SSLerr(SSL_F_SSL_SHUTDOWN, SSL_R_SHUTDOWN_WHILE_IN_INIT);
        return -1;
    }
}