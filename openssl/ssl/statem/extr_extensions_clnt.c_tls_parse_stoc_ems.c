#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {int options; TYPE_2__* session; int /*<<< orphan*/  hit; TYPE_1__ s3; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_3__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 int SSL_OP_NO_EXTENDED_MASTER_SECRET ; 
 int /*<<< orphan*/  SSL_SESS_FLAG_EXTMS ; 
 int /*<<< orphan*/  TLS1_FLAGS_RECEIVED_EXTMS ; 

int tls_parse_stoc_ems(SSL *s, PACKET *pkt, unsigned int context, X509 *x,
                       size_t chainidx)
{
    if (s->options & SSL_OP_NO_EXTENDED_MASTER_SECRET)
        return 1;
    s->s3.flags |= TLS1_FLAGS_RECEIVED_EXTMS;
    if (!s->hit)
        s->session->flags |= SSL_SESS_FLAG_EXTMS;

    return 1;
}