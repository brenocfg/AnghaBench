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
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_GET_REASON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_get_error () ; 
 int /*<<< orphan*/  SETUP_CIPHERLIST_TEST_FIXTURE () ; 
 int /*<<< orphan*/  SSL_CTX_set_cipher_list (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SSL_R_NO_CIPHER_MATCH ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_cipher_list (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 TYPE_1__* fixture ; 
 int result ; 
 int /*<<< orphan*/  tear_down (TYPE_1__*) ; 

__attribute__((used)) static int test_default_cipherlist_clear(void)
{
    SETUP_CIPHERLIST_TEST_FIXTURE();
    SSL *s = NULL;

    if (fixture == NULL)
        return 0;

    if (!TEST_int_eq(SSL_CTX_set_cipher_list(fixture->server, "no-such"), 0))
        goto end;

    if (!TEST_int_eq(ERR_GET_REASON(ERR_get_error()), SSL_R_NO_CIPHER_MATCH))
        goto end;

    s = SSL_new(fixture->client);

    if (!TEST_ptr(s))
      goto end;

    if (!TEST_int_eq(SSL_set_cipher_list(s, "no-such"), 0))
        goto end;

    if (!TEST_int_eq(ERR_GET_REASON(ERR_get_error()),
                SSL_R_NO_CIPHER_MATCH))
        goto end;

    result = 1;
end:
    SSL_free(s);
    tear_down(fixture);
    return result;
}