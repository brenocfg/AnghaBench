#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * sigalg; } ;
struct TYPE_9__ {TYPE_1__ tmp; } ;
struct TYPE_11__ {TYPE_3__* cert; TYPE_2__ s3; } ;
struct TYPE_10__ {int cert_flags; } ;
typedef  TYPE_4__ SSL ;

/* Variables and functions */
 int SSL_CERT_FLAGS_CHECK_TLS_STRICT ; 
 int /*<<< orphan*/  tls1_check_chain (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tls_choose_sigalg (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssl3_check_client_certificate(SSL *s)
{
    /* If no suitable signature algorithm can't use certificate */
    if (!tls_choose_sigalg(s, 0) || s->s3.tmp.sigalg == NULL)
        return 0;
    /*
     * If strict mode check suitability of chain before using it. This also
     * adjusts suite B digest if necessary.
     */
    if (s->cert->cert_flags & SSL_CERT_FLAGS_CHECK_TLS_STRICT &&
        !tls1_check_chain(s, NULL, NULL, NULL, -2))
        return 0;
    return 1;
}