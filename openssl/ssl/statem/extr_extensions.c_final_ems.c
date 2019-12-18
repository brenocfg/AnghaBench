#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; } ;
struct TYPE_8__ {TYPE_2__* session; TYPE_1__ s3; scalar_t__ hit; int /*<<< orphan*/  server; } ;
struct TYPE_7__ {int flags; } ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_AD_HANDSHAKE_FAILURE ; 
 int /*<<< orphan*/  SSL_F_FINAL_EMS ; 
 int /*<<< orphan*/  SSL_R_INCONSISTENT_EXTMS ; 
 int SSL_SESS_FLAG_EXTMS ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TLS1_FLAGS_RECEIVED_EXTMS ; 

__attribute__((used)) static int final_ems(SSL *s, unsigned int context, int sent)
{
    if (!s->server && s->hit) {
        /*
         * Check extended master secret extension is consistent with
         * original session.
         */
        if (!(s->s3.flags & TLS1_FLAGS_RECEIVED_EXTMS) !=
            !(s->session->flags & SSL_SESS_FLAG_EXTMS)) {
            SSLfatal(s, SSL_AD_HANDSHAKE_FAILURE, SSL_F_FINAL_EMS,
                     SSL_R_INCONSISTENT_EXTMS);
            return 0;
        }
    }

    return 1;
}