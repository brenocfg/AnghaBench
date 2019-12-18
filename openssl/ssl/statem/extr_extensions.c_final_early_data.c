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
struct TYPE_7__ {int /*<<< orphan*/  early_data; int /*<<< orphan*/  early_data_ok; } ;
struct TYPE_8__ {scalar_t__ max_early_data; scalar_t__ early_data_state; scalar_t__ hello_retry_request; TYPE_1__ ext; int /*<<< orphan*/  allow_early_data_cb_data; int /*<<< orphan*/  (* allow_early_data_cb ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  hit; int /*<<< orphan*/  server; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int SSL3_CC_EARLY ; 
 int SSL3_CHANGE_CIPHER_SERVER_READ ; 
 int /*<<< orphan*/  SSL_AD_ILLEGAL_PARAMETER ; 
 int /*<<< orphan*/  SSL_EARLY_DATA_ACCEPTED ; 
 scalar_t__ SSL_EARLY_DATA_ACCEPTING ; 
 int /*<<< orphan*/  SSL_EARLY_DATA_REJECTED ; 
 unsigned int SSL_EXT_TLS1_3_ENCRYPTED_EXTENSIONS ; 
 int /*<<< orphan*/  SSL_F_FINAL_EARLY_DATA ; 
 scalar_t__ SSL_HRR_NONE ; 
 int /*<<< orphan*/  SSL_R_BAD_EARLY_DATA ; 
 int /*<<< orphan*/  SSLfatal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls13_change_cipher_state (TYPE_2__*,int) ; 

__attribute__((used)) static int final_early_data(SSL *s, unsigned int context, int sent)
{
    if (!sent)
        return 1;

    if (!s->server) {
        if (context == SSL_EXT_TLS1_3_ENCRYPTED_EXTENSIONS
                && sent
                && !s->ext.early_data_ok) {
            /*
             * If we get here then the server accepted our early_data but we
             * later realised that it shouldn't have done (e.g. inconsistent
             * ALPN)
             */
            SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER, SSL_F_FINAL_EARLY_DATA,
                     SSL_R_BAD_EARLY_DATA);
            return 0;
        }

        return 1;
    }

    if (s->max_early_data == 0
            || !s->hit
            || s->early_data_state != SSL_EARLY_DATA_ACCEPTING
            || !s->ext.early_data_ok
            || s->hello_retry_request != SSL_HRR_NONE
            || (s->allow_early_data_cb != NULL
                && !s->allow_early_data_cb(s,
                                         s->allow_early_data_cb_data))) {
        s->ext.early_data = SSL_EARLY_DATA_REJECTED;
    } else {
        s->ext.early_data = SSL_EARLY_DATA_ACCEPTED;

        if (!tls13_change_cipher_state(s,
                    SSL3_CC_EARLY | SSL3_CHANGE_CIPHER_SERVER_READ)) {
            /* SSLfatal() already called */
            return 0;
        }
    }

    return 1;
}