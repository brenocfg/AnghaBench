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

/* Variables and functions */
 int /*<<< orphan*/  RUN_ONCE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ssl_x509_store_ctx_idx ; 
 int /*<<< orphan*/  ssl_x509_store_ctx_init ; 
 int /*<<< orphan*/  ssl_x509_store_ctx_once ; 

int SSL_get_ex_data_X509_STORE_CTX_idx(void)
{

    if (!RUN_ONCE(&ssl_x509_store_ctx_once, ssl_x509_store_ctx_init))
        return -1;
    return ssl_x509_store_ctx_idx;
}