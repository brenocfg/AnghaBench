#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {int options; TYPE_1__ s3; } ;
typedef  TYPE_2__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 scalar_t__ PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_PARSE_CTOS_EMS ; 
 int SSL_OP_NO_EXTENDED_MASTER_SECRET ; 
 int /*<<< orphan*/  SSL_R_BAD_EXTENSION ; 
 int /*<<< orphan*/  SSLfatal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS1_FLAGS_RECEIVED_EXTMS ; 

int tls_parse_ctos_ems(SSL *s, PACKET *pkt, unsigned int context, X509 *x,
                       size_t chainidx)
{
    /* The extension must always be empty */
    if (PACKET_remaining(pkt) != 0) {
        SSLfatal(s, SSL_AD_DECODE_ERROR,
                 SSL_F_TLS_PARSE_CTOS_EMS, SSL_R_BAD_EXTENSION);
        return 0;
    }

    if (s->options & SSL_OP_NO_EXTENDED_MASTER_SECRET)
        return 1;

    s->s3.flags |= TLS1_FLAGS_RECEIVED_EXTMS;

    return 1;
}