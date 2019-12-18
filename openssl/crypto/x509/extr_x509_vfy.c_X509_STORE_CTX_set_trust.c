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
typedef  int /*<<< orphan*/  X509_STORE_CTX ;

/* Variables and functions */
 int X509_STORE_CTX_purpose_inherit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int X509_STORE_CTX_set_trust(X509_STORE_CTX *ctx, int trust)
{
    /*
     * XXX: See above, this function would only be needed when the default
     * trust for the purpose needs an override in a corner case.
     */
    return X509_STORE_CTX_purpose_inherit(ctx, 0, 0, trust);
}