#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORK_STATE ;
struct TYPE_7__ {int hand_state; } ;
struct TYPE_6__ {TYPE_2__ statem; } ;
typedef  TYPE_1__ SSL ;
typedef  TYPE_2__ OSSL_STATEM ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_OSSL_STATEM_CLIENT_POST_PROCESS_MESSAGE ; 
 int /*<<< orphan*/  SSLfatal (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  TLS_ST_CR_CERT_REQ 129 
#define  TLS_ST_CR_CERT_VRFY 128 
 int /*<<< orphan*/  WORK_ERROR ; 
 int /*<<< orphan*/  tls_prepare_client_certificate (TYPE_1__*,int /*<<< orphan*/ ) ; 

WORK_STATE ossl_statem_client_post_process_message(SSL *s, WORK_STATE wst)
{
    OSSL_STATEM *st = &s->statem;

    switch (st->hand_state) {
    default:
        /* Shouldn't happen */
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_OSSL_STATEM_CLIENT_POST_PROCESS_MESSAGE,
                 ERR_R_INTERNAL_ERROR);
        return WORK_ERROR;

    case TLS_ST_CR_CERT_VRFY:
    case TLS_ST_CR_CERT_REQ:
        return tls_prepare_client_certificate(s, wst);
    }
}