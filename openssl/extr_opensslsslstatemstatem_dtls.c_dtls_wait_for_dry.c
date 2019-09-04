#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORK_STATE ;
struct TYPE_8__ {int in_read_app_data; } ;
struct TYPE_9__ {int /*<<< orphan*/  rwstate; TYPE_1__ s3; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_clear_retry_flags (int /*<<< orphan*/ ) ; 
 int BIO_dgram_sctp_wait_for_dry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_set_retry_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_UNEXPECTED_MESSAGE ; 
 int /*<<< orphan*/  SSL_F_DTLS_WAIT_FOR_DRY ; 
 int /*<<< orphan*/  SSL_READING ; 
 int /*<<< orphan*/  SSL_R_UNEXPECTED_MESSAGE ; 
 int /*<<< orphan*/  SSL_get_rbio (TYPE_2__*) ; 
 int /*<<< orphan*/  SSL_get_wbio (TYPE_2__*) ; 
 int /*<<< orphan*/  SSLfatal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WORK_ERROR ; 
 int /*<<< orphan*/  WORK_FINISHED_CONTINUE ; 
 int /*<<< orphan*/  WORK_MORE_A ; 
 scalar_t__ dtls_get_reassembled_message (TYPE_2__*,int*,size_t*) ; 

WORK_STATE dtls_wait_for_dry(SSL *s)
{
    int ret, errtype;
    size_t len;

    /* read app data until dry event */
    ret = BIO_dgram_sctp_wait_for_dry(SSL_get_wbio(s));
    if (ret < 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DTLS_WAIT_FOR_DRY,
                 ERR_R_INTERNAL_ERROR);
        return WORK_ERROR;
    }

    if (ret == 0) {
        /*
         * We're not expecting any more messages from the peer at this point -
         * but we could get an alert. If an alert is waiting then we will never
         * return successfully. Therefore we attempt to read a message. This
         * should never succeed but will process any waiting alerts.
         */
        if (dtls_get_reassembled_message(s, &errtype, &len)) {
            /* The call succeeded! This should never happen */
            SSLfatal(s, SSL_AD_UNEXPECTED_MESSAGE, SSL_F_DTLS_WAIT_FOR_DRY,
                     SSL_R_UNEXPECTED_MESSAGE);
            return WORK_ERROR;
        }

        s->s3.in_read_app_data = 2;
        s->rwstate = SSL_READING;
        BIO_clear_retry_flags(SSL_get_rbio(s));
        BIO_set_retry_read(SSL_get_rbio(s));
        return WORK_MORE_A;
    }
    return WORK_FINISHED_CONTINUE;
}