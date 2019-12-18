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
 int /*<<< orphan*/  X509_STORE_CTX_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_V_ERR_APPLICATION_VERIFICATION ; 

__attribute__((used)) static int verify_reject_cb(X509_STORE_CTX *ctx, void *arg) {
    X509_STORE_CTX_set_error(ctx, X509_V_ERR_APPLICATION_VERIFICATION);
    return 0;
}