#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int key_update; } ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_F_SSL_KEY_UPDATE ; 
 int /*<<< orphan*/  SSL_IS_TLS13 (TYPE_1__*) ; 
 int SSL_KEY_UPDATE_NOT_REQUESTED ; 
 int SSL_KEY_UPDATE_REQUESTED ; 
 int /*<<< orphan*/  SSL_R_INVALID_KEY_UPDATE_TYPE ; 
 int /*<<< orphan*/  SSL_R_STILL_IN_INIT ; 
 int /*<<< orphan*/  SSL_R_WRONG_SSL_VERSION ; 
 int /*<<< orphan*/  SSL_is_init_finished (TYPE_1__*) ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ossl_statem_set_in_init (TYPE_1__*,int) ; 

int SSL_key_update(SSL *s, int updatetype)
{
    /*
     * TODO(TLS1.3): How will applications know whether TLSv1.3 has been
     * negotiated, and that it is appropriate to call SSL_key_update() instead
     * of SSL_renegotiate().
     */
    if (!SSL_IS_TLS13(s)) {
        SSLerr(SSL_F_SSL_KEY_UPDATE, SSL_R_WRONG_SSL_VERSION);
        return 0;
    }

    if (updatetype != SSL_KEY_UPDATE_NOT_REQUESTED
            && updatetype != SSL_KEY_UPDATE_REQUESTED) {
        SSLerr(SSL_F_SSL_KEY_UPDATE, SSL_R_INVALID_KEY_UPDATE_TYPE);
        return 0;
    }

    if (!SSL_is_init_finished(s)) {
        SSLerr(SSL_F_SSL_KEY_UPDATE, SSL_R_STILL_IN_INIT);
        return 0;
    }

    ossl_statem_set_in_init(s, 1);
    s->key_update = updatetype;
    return 1;
}