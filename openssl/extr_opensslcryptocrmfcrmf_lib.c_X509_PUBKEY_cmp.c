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
typedef  int /*<<< orphan*/  X509_PUBKEY ;
typedef  int /*<<< orphan*/  X509_ALGOR ;

/* Variables and functions */
 int EVP_PKEY_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int X509_ALGOR_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_PUBKEY_get0 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_PUBKEY_get0_param (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int X509_PUBKEY_cmp(X509_PUBKEY *a, X509_PUBKEY *b)
{
    X509_ALGOR *algA = NULL, *algB = NULL;
    int res = 0;

    if (a == b)
        return 0;
    if (a == NULL || !X509_PUBKEY_get0_param(NULL, NULL, NULL, &algA, a)
            || algA == NULL)
        return -1;
    if (b == NULL || !X509_PUBKEY_get0_param(NULL, NULL, NULL, &algB, b)
            || algB == NULL)
        return 1;
    if ((res = X509_ALGOR_cmp(algA, algB)) != 0)
        return res;
    return EVP_PKEY_cmp(X509_PUBKEY_get0(a), X509_PUBKEY_get0(b));
}