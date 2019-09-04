#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ex_nscert; int ex_flags; } ;
typedef  TYPE_1__ X509 ;

/* Variables and functions */
 int EXFLAG_NSCERT ; 
 int NS_SMIME ; 
 int NS_SMIME_CA ; 
 int NS_SSL_CLIENT ; 
 int /*<<< orphan*/  XKU_SMIME ; 
 int check_ca (TYPE_1__ const*) ; 
 scalar_t__ xku_reject (TYPE_1__ const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int purpose_smime(const X509 *x, int ca)
{
    if (xku_reject(x, XKU_SMIME))
        return 0;
    if (ca) {
        int ca_ret;
        ca_ret = check_ca(x);
        if (!ca_ret)
            return 0;
        /* check nsCertType if present */
        if (ca_ret != 5 || x->ex_nscert & NS_SMIME_CA)
            return ca_ret;
        else
            return 0;
    }
    if (x->ex_flags & EXFLAG_NSCERT) {
        if (x->ex_nscert & NS_SMIME)
            return 1;
        /* Workaround for some buggy certificates */
        if (x->ex_nscert & NS_SSL_CLIENT)
            return 2;
        return 0;
    }
    return 1;
}