#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * s; int /*<<< orphan*/ * r; } ;
typedef  TYPE_1__ DSA_SIG ;

/* Variables and functions */
 void* BN_new () ; 
 int /*<<< orphan*/  DSA_SIG_free (TYPE_1__*) ; 
 TYPE_1__* DSA_SIG_new () ; 
 scalar_t__ decode_der_dsa_sig (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char const**,size_t) ; 

DSA_SIG *d2i_DSA_SIG(DSA_SIG **psig, const unsigned char **ppin, long len)
{
    DSA_SIG *sig;

    if (len < 0)
        return NULL;
    if (psig != NULL && *psig != NULL) {
        sig = *psig;
    } else {
        sig = DSA_SIG_new();
        if (sig == NULL)
            return NULL;
    }
    if (sig->r == NULL)
        sig->r = BN_new();
    if (sig->s == NULL)
        sig->s = BN_new();
    if (decode_der_dsa_sig(sig->r, sig->s, ppin, (size_t)len) == 0) {
        if (psig == NULL || *psig == NULL)
            DSA_SIG_free(sig);
        return NULL;
    }
    if (psig != NULL && *psig == NULL)
        *psig = sig;
    return sig;
}