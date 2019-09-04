#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_5__ {size_t shared_sigalgslen; TYPE_1__** shared_sigalgs; } ;
struct TYPE_4__ {int sigandhash; } ;
typedef  TYPE_2__ CERT ;

/* Variables and functions */
 int X509_get_signature_nid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tls1_check_sig_alg(CERT *c, X509 *x, int default_nid)
{
    int sig_nid;
    size_t i;
    if (default_nid == -1)
        return 1;
    sig_nid = X509_get_signature_nid(x);
    if (default_nid)
        return sig_nid == default_nid ? 1 : 0;
    for (i = 0; i < c->shared_sigalgslen; i++)
        if (sig_nid == c->shared_sigalgs[i]->sigandhash)
            return 1;
    return 0;
}