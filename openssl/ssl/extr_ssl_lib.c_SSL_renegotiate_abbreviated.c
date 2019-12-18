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
struct TYPE_7__ {int options; int renegotiate; TYPE_1__* method; scalar_t__ new_session; } ;
struct TYPE_6__ {int (* ssl_renegotiate ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_F_SSL_RENEGOTIATE_ABBREVIATED ; 
 scalar_t__ SSL_IS_TLS13 (TYPE_2__*) ; 
 int SSL_OP_NO_RENEGOTIATION ; 
 int /*<<< orphan*/  SSL_R_NO_RENEGOTIATION ; 
 int /*<<< orphan*/  SSL_R_WRONG_SSL_VERSION ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*) ; 

int SSL_renegotiate_abbreviated(SSL *s)
{
    if (SSL_IS_TLS13(s)) {
        SSLerr(SSL_F_SSL_RENEGOTIATE_ABBREVIATED, SSL_R_WRONG_SSL_VERSION);
        return 0;
    }

    if ((s->options & SSL_OP_NO_RENEGOTIATION)) {
        SSLerr(SSL_F_SSL_RENEGOTIATE_ABBREVIATED, SSL_R_NO_RENEGOTIATION);
        return 0;
    }

    s->renegotiate = 1;
    s->new_session = 0;

    return s->method->ssl_renegotiate(s);
}