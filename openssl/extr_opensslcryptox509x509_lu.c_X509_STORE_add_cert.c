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
typedef  int /*<<< orphan*/  X509_STORE ;
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  X509_F_X509_STORE_ADD_CERT ; 
 int /*<<< orphan*/  X509err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x509_store_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int X509_STORE_add_cert(X509_STORE *ctx, X509 *x)
{
    if (!x509_store_add(ctx, x, 0)) {
        X509err(X509_F_X509_STORE_ADD_CERT, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    return 1;
}