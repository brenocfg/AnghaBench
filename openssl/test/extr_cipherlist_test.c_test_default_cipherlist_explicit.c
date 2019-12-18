#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  client; int /*<<< orphan*/  server; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXECUTE_CIPHERLIST_TEST () ; 
 int /*<<< orphan*/  SETUP_CIPHERLIST_TEST_FIXTURE () ; 
 int /*<<< orphan*/  SSL_CTX_set_cipher_list (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 TYPE_1__* fixture ; 
 int result ; 
 int /*<<< orphan*/  tear_down (TYPE_1__*) ; 

__attribute__((used)) static int test_default_cipherlist_explicit(void)
{
    SETUP_CIPHERLIST_TEST_FIXTURE();
    if (fixture == NULL)
        return 0;
    if (!TEST_true(SSL_CTX_set_cipher_list(fixture->server, "DEFAULT"))
            || !TEST_true(SSL_CTX_set_cipher_list(fixture->client, "DEFAULT")))
        tear_down(fixture);
    EXECUTE_CIPHERLIST_TEST();
    return result;
}