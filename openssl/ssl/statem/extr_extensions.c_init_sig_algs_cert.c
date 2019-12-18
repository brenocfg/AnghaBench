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
struct TYPE_5__ {int /*<<< orphan*/ * peer_cert_sigalgs; } ;
struct TYPE_6__ {TYPE_1__ tmp; } ;
struct TYPE_7__ {TYPE_2__ s3; } ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_sig_algs_cert(SSL *s, unsigned int context)
{
    /* Clear any signature algorithms extension received */
    OPENSSL_free(s->s3.tmp.peer_cert_sigalgs);
    s->s3.tmp.peer_cert_sigalgs = NULL;

    return 1;
}