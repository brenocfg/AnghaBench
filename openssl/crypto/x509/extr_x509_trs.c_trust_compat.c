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
typedef  int /*<<< orphan*/  X509_TRUST ;
struct TYPE_4__ {int ex_flags; } ;
typedef  TYPE_1__ X509 ;

/* Variables and functions */
 int EXFLAG_SS ; 
 int X509_TRUST_NO_SS_COMPAT ; 
 int X509_TRUST_TRUSTED ; 
 int X509_TRUST_UNTRUSTED ; 
 int /*<<< orphan*/  X509_check_purpose (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int trust_compat(X509_TRUST *trust, X509 *x, int flags)
{
    /* Call for side-effect of computing hash and caching extensions */
    X509_check_purpose(x, -1, 0);
    if ((flags & X509_TRUST_NO_SS_COMPAT) == 0 && x->ex_flags & EXFLAG_SS)
        return X509_TRUST_TRUSTED;
    else
        return X509_TRUST_UNTRUSTED;
}