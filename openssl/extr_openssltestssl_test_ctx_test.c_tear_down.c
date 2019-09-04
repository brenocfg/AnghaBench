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
struct TYPE_4__ {int /*<<< orphan*/  expected_ctx; } ;
typedef  TYPE_1__ SSL_TEST_CTX_TEST_FIXTURE ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  SSL_TEST_CTX_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tear_down(SSL_TEST_CTX_TEST_FIXTURE *fixture)
{
    SSL_TEST_CTX_free(fixture->expected_ctx);
    OPENSSL_free(fixture);
}