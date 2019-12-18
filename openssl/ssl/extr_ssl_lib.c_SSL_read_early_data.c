#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  early_data; } ;
struct TYPE_8__ {int early_data_state; TYPE_1__ ext; int /*<<< orphan*/  server; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED ; 
 int /*<<< orphan*/  SSL_EARLY_DATA_ACCEPTED ; 
 int SSL_EARLY_DATA_ACCEPTING ; 
#define  SSL_EARLY_DATA_ACCEPT_RETRY 130 
 int SSL_EARLY_DATA_FINISHED_READING ; 
#define  SSL_EARLY_DATA_NONE 129 
 int SSL_EARLY_DATA_READING ; 
#define  SSL_EARLY_DATA_READ_RETRY 128 
 int /*<<< orphan*/  SSL_F_SSL_READ_EARLY_DATA ; 
 int SSL_READ_EARLY_DATA_ERROR ; 
 int SSL_READ_EARLY_DATA_FINISH ; 
 int SSL_READ_EARLY_DATA_SUCCESS ; 
 int SSL_accept (TYPE_2__*) ; 
 int /*<<< orphan*/  SSL_in_before (TYPE_2__*) ; 
 int SSL_read_ex (TYPE_2__*,void*,size_t,size_t*) ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int SSL_read_early_data(SSL *s, void *buf, size_t num, size_t *readbytes)
{
    int ret;

    if (!s->server) {
        SSLerr(SSL_F_SSL_READ_EARLY_DATA, ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED);
        return SSL_READ_EARLY_DATA_ERROR;
    }

    switch (s->early_data_state) {
    case SSL_EARLY_DATA_NONE:
        if (!SSL_in_before(s)) {
            SSLerr(SSL_F_SSL_READ_EARLY_DATA,
                   ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED);
            return SSL_READ_EARLY_DATA_ERROR;
        }
        /* fall through */

    case SSL_EARLY_DATA_ACCEPT_RETRY:
        s->early_data_state = SSL_EARLY_DATA_ACCEPTING;
        ret = SSL_accept(s);
        if (ret <= 0) {
            /* NBIO or error */
            s->early_data_state = SSL_EARLY_DATA_ACCEPT_RETRY;
            return SSL_READ_EARLY_DATA_ERROR;
        }
        /* fall through */

    case SSL_EARLY_DATA_READ_RETRY:
        if (s->ext.early_data == SSL_EARLY_DATA_ACCEPTED) {
            s->early_data_state = SSL_EARLY_DATA_READING;
            ret = SSL_read_ex(s, buf, num, readbytes);
            /*
             * State machine will update early_data_state to
             * SSL_EARLY_DATA_FINISHED_READING if we get an EndOfEarlyData
             * message
             */
            if (ret > 0 || (ret <= 0 && s->early_data_state
                                        != SSL_EARLY_DATA_FINISHED_READING)) {
                s->early_data_state = SSL_EARLY_DATA_READ_RETRY;
                return ret > 0 ? SSL_READ_EARLY_DATA_SUCCESS
                               : SSL_READ_EARLY_DATA_ERROR;
            }
        } else {
            s->early_data_state = SSL_EARLY_DATA_FINISHED_READING;
        }
        *readbytes = 0;
        return SSL_READ_EARLY_DATA_FINISH;

    default:
        SSLerr(SSL_F_SSL_READ_EARLY_DATA, ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED);
        return SSL_READ_EARLY_DATA_ERROR;
    }
}