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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_NOCLOSE ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_fp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMP_R_NO_STDIO ; 
 int /*<<< orphan*/  CMPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_TRACE_CATEGORY_CMP ; 
 scalar_t__ OSSL_trace_set_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 

int OSSL_CMP_log_open(void) /* is designed to be idempotent */
{
#ifndef OPENSSL_NO_STDIO
    BIO *bio = BIO_new_fp(stdout, BIO_NOCLOSE);

    if (bio != NULL && OSSL_trace_set_channel(OSSL_TRACE_CATEGORY_CMP, bio))
        return 1;
    BIO_free(bio);
#endif
    CMPerr(0, CMP_R_NO_STDIO);
    return 0;
}