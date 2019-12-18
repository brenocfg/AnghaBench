#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  DSA_SIG ;

/* Variables and functions */
 int /*<<< orphan*/  DSA_F_DSA_SIG_NEW ; 
 int /*<<< orphan*/  DSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/ * OPENSSL_zalloc (int) ; 

DSA_SIG *DSA_SIG_new(void)
{
    DSA_SIG *sig = OPENSSL_zalloc(sizeof(*sig));
    if (sig == NULL)
        DSAerr(DSA_F_DSA_SIG_NEW, ERR_R_MALLOC_FAILURE);
    return sig;
}