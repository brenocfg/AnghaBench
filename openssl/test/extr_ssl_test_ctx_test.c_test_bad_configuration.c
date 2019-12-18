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
typedef  int /*<<< orphan*/  SSL_TEST_CTX ;

/* Variables and functions */
 int /*<<< orphan*/ * SSL_TEST_CTX_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_TEST_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr_null (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bad_configurations ; 
 int /*<<< orphan*/  conf ; 

__attribute__((used)) static int test_bad_configuration(int idx)
{
    SSL_TEST_CTX *ctx;

    if (!TEST_ptr_null(ctx = SSL_TEST_CTX_create(conf,
                                                 bad_configurations[idx]))) {
        SSL_TEST_CTX_free(ctx);
        return 0;
    }

    return 1;
}