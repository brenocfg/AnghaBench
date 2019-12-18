#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_9__ {TYPE_1__* d1; TYPE_2__* ctx; } ;
struct TYPE_8__ {scalar_t__ (* app_gen_cookie_cb ) (TYPE_3__*,int /*<<< orphan*/ ,unsigned int*) ;} ;
struct TYPE_7__ {unsigned int cookie_len; int /*<<< orphan*/  cookie; } ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_NO_ALERT ; 
 int /*<<< orphan*/  SSL_F_DTLS_CONSTRUCT_HELLO_VERIFY_REQUEST ; 
 int /*<<< orphan*/  SSL_R_COOKIE_GEN_CALLBACK_FAILURE ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtls_raw_hello_verify_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ stub1 (TYPE_3__*,int /*<<< orphan*/ ,unsigned int*) ; 

int dtls_construct_hello_verify_request(SSL *s, WPACKET *pkt)
{
    unsigned int cookie_leni;
    if (s->ctx->app_gen_cookie_cb == NULL ||
        s->ctx->app_gen_cookie_cb(s, s->d1->cookie,
                                  &cookie_leni) == 0 ||
        cookie_leni > 255) {
        SSLfatal(s, SSL_AD_NO_ALERT, SSL_F_DTLS_CONSTRUCT_HELLO_VERIFY_REQUEST,
                 SSL_R_COOKIE_GEN_CALLBACK_FAILURE);
        return 0;
    }
    s->d1->cookie_len = cookie_leni;

    if (!dtls_raw_hello_verify_request(pkt, s->d1->cookie,
                                              s->d1->cookie_len)) {
        SSLfatal(s, SSL_AD_NO_ALERT, SSL_F_DTLS_CONSTRUCT_HELLO_VERIFY_REQUEST,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }

    return 1;
}