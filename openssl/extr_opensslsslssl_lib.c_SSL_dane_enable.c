#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * hostname; } ;
struct TYPE_11__ {int mdpth; int pdpth; int /*<<< orphan*/ * trecs; TYPE_2__* dctx; } ;
struct TYPE_12__ {TYPE_3__* ctx; int /*<<< orphan*/  param; TYPE_1__ ext; TYPE_4__ dane; } ;
struct TYPE_9__ {scalar_t__ mdmax; } ;
struct TYPE_10__ {TYPE_2__ dane; } ;
typedef  TYPE_4__ SSL_DANE ;
typedef  TYPE_5__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  SSL_F_SSL_DANE_ENABLE ; 
 int /*<<< orphan*/  SSL_R_CONTEXT_NOT_DANE_ENABLED ; 
 int /*<<< orphan*/  SSL_R_DANE_ALREADY_ENABLED ; 
 int /*<<< orphan*/  SSL_R_ERROR_SETTING_TLSA_BASE_DOMAIN ; 
 int /*<<< orphan*/  SSL_set_tlsext_host_name (TYPE_5__*,char const*) ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_VERIFY_PARAM_set1_host (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sk_danetls_record_new_null () ; 

int SSL_dane_enable(SSL *s, const char *basedomain)
{
    SSL_DANE *dane = &s->dane;

    if (s->ctx->dane.mdmax == 0) {
        SSLerr(SSL_F_SSL_DANE_ENABLE, SSL_R_CONTEXT_NOT_DANE_ENABLED);
        return 0;
    }
    if (dane->trecs != NULL) {
        SSLerr(SSL_F_SSL_DANE_ENABLE, SSL_R_DANE_ALREADY_ENABLED);
        return 0;
    }

    /*
     * Default SNI name.  This rejects empty names, while set1_host below
     * accepts them and disables host name checks.  To avoid side-effects with
     * invalid input, set the SNI name first.
     */
    if (s->ext.hostname == NULL) {
        if (!SSL_set_tlsext_host_name(s, basedomain)) {
            SSLerr(SSL_F_SSL_DANE_ENABLE, SSL_R_ERROR_SETTING_TLSA_BASE_DOMAIN);
            return -1;
        }
    }

    /* Primary RFC6125 reference identifier */
    if (!X509_VERIFY_PARAM_set1_host(s->param, basedomain, 0)) {
        SSLerr(SSL_F_SSL_DANE_ENABLE, SSL_R_ERROR_SETTING_TLSA_BASE_DOMAIN);
        return -1;
    }

    dane->mdpth = -1;
    dane->pdpth = -1;
    dane->dctx = &s->ctx->dane;
    dane->trecs = sk_danetls_record_new_null();

    if (dane->trecs == NULL) {
        SSLerr(SSL_F_SSL_DANE_ENABLE, ERR_R_MALLOC_FAILURE);
        return -1;
    }
    return 1;
}