#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_4__ {int sig_idx; } ;
typedef  int /*<<< orphan*/  SSL ;
typedef  TYPE_1__ SIGALG_LOOKUP ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int check_cert_usable (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ssl_cert_lookup_by_pkey (int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static int is_cert_usable(SSL *s, const SIGALG_LOOKUP *sig, X509 *x,
                          EVP_PKEY *pkey)
{
    size_t idx;

    if (ssl_cert_lookup_by_pkey(pkey, &idx) == NULL)
        return 0;

    /* Check the key is consistent with the sig alg */
    if ((int)idx != sig->sig_idx)
        return 0;

    return check_cert_usable(s, sig, x, pkey);
}